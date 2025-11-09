#pragma once
#include "EmployeeNode.h"
#include "EmployeeTreeView.h"

using namespace System;
using namespace System::Data;
using namespace System::Data::SqlClient;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Collections::Generic;

public ref class EmployeeHandler
{
private:
    static List<String^>^ recentSearches = gcnew List<String^>();
// For Helper method for TreeView
private:

    List<EmployeeNode^>^ BuildTreeFromDatabase()
    {
        DataTable^ employees = EmployeeHandler::GetAllEmployeesSorted();
        Dictionary<int, EmployeeNode^>^ nodeMap = gcnew Dictionary<int, EmployeeNode^>();

        // 1. Create all nodes
        for each(DataRow ^ row in employees->Rows)
        {
            int id = Convert::ToInt32(row["EmployeeID"]);
            String^ name = row["FullName"]->ToString();
            String^ pos = row["Position"]->ToString();
            nodeMap[id] = gcnew EmployeeNode(name, pos, id);
        }

        // 2. Build parent-child relationships
        for each(DataRow ^ row in employees->Rows)
        {
            int empId = Convert::ToInt32(row["EmployeeID"]);
            int parentId = Convert::ToInt32(row["ParentID"]);

            if (parentId != 0 && nodeMap->ContainsKey(parentId))
            {
                nodeMap[parentId]->AddChild(nodeMap[empId]);
            }
        }

        // 3. Collect roots (nodes with ParentID == 0)
        List<EmployeeNode^>^ roots = gcnew List<EmployeeNode^>();
        for each(DataRow ^ row in employees->Rows)
        {
            int empId = Convert::ToInt32(row["EmployeeID"]);
            int parentId = Convert::ToInt32(row["ParentID"]);

            EmployeeNode^ currentNode = nodeMap[empId];

            if (parentId == 0)
            {
                // Only add to roots if not already added
                if (!roots->Contains(currentNode))
                    roots->Add(currentNode);
            }
            else if (nodeMap->ContainsKey(parentId))
            {
                EmployeeNode^ parentNode = nodeMap[parentId];

                // Only add if currentNode is not already a child
                bool alreadyChild = false;
                for each(EmployeeNode ^ child in parentNode->Children)
                {
                    if (child->ID == currentNode->ID)
                    {
                        alreadyChild = true;
                        break;
                    }
                }

                if (!alreadyChild)
                    parentNode->AddChild(currentNode);
            }
        }

        for each(auto kvp in nodeMap)
        {
            Console::WriteLine("{0} ({1}) -> {2} children", kvp.Value->Name, kvp.Key, kvp.Value->Children->Count);
            for each(auto child in kvp.Value->Children)
                Console::WriteLine("    {0} ({1})", child->Name, child->ID);
        }

        return roots;
    }




public:
    void ShowEmployeeHierarchy()
    {
        List<EmployeeNode^>^ roots = BuildTreeFromDatabase();

        if (roots->Count > 0)
        {
            DSAPROJECTFINALIZED::EmployeeTreeView^ treeForm =
                gcnew DSAPROJECTFINALIZED::EmployeeTreeView(roots);
            treeForm->ShowDialog();
        }
        else
        {
            MessageBox::Show("No employee hierarchy found in database!");
        }
    }

// End
public:
    static String^ connectionString =
        "Data Source=alvinjohndano\\sqlexpress;Initial Catalog=LPO_DSA;Integrated Security=True;";

    static DataTable^ GetAllEmployeesSorted()
    {
        DataTable^ table = gcnew DataTable();

        try {
            SqlConnection^ con = gcnew SqlConnection(connectionString);
            con->Open();

            String^ query = "SELECT * FROM dbo.Employees ORDER BY EmployeeID ASC";
            SqlDataAdapter^ adapter = gcnew SqlDataAdapter(query, con);
            adapter->Fill(table);

            con->Close();
        }
        catch (Exception^ ex) {
            MessageBox::Show("Error fetching employees: " + ex->Message,
                "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }

        return table;
    }

    static DataTable^ SearchEmployees(String^ query)
    {
        DataTable^ table = gcnew DataTable();

        try {
            SqlConnection^ con = gcnew SqlConnection(connectionString);
            con->Open();

            String^ trimmed = query->Trim();
            SqlCommand^ cmd = gcnew SqlCommand();
            cmd->Connection = con;

            bool isNumeric = true;
            for each(wchar_t c in trimmed) {
                if (!Char::IsDigit(c)) { isNumeric = false; break; }
            }

            array<String^>^ positions = { "ceo", "manager", "employee" };
            bool isPosition = false;
            for each(String ^ pos in positions) {
                if (trimmed->ToLower()->StartsWith(pos->ToLower())) {
                    isPosition = true;
                    break;
                }
            }

            if (isNumeric) {
                cmd->CommandText = "SELECT * FROM dbo.Employees WHERE EmployeeID = @id";
                cmd->Parameters->AddWithValue("@id", Convert::ToInt32(trimmed));
            }
            else if (isPosition) {
                cmd->CommandText = "SELECT * FROM dbo.Employees WHERE LOWER(Position) LIKE @pos + '%'";
                cmd->Parameters->AddWithValue("@pos", trimmed->ToLower());
            }
            else {
                cmd->CommandText = "SELECT * FROM dbo.Employees WHERE LOWER(FullName) LIKE @name + '%'";
                cmd->Parameters->AddWithValue("@name", trimmed->ToLower());
            }

            SqlDataAdapter^ adapter = gcnew SqlDataAdapter(cmd);
            adapter->Fill(table);

            AddRecent(trimmed);

            con->Close();
        }
        catch (Exception^ ex) {
            MessageBox::Show("Error searching employees: " + ex->Message,
                "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }

        return table;
    }

    static void AddRecent(String^ query)
    {
        if (!String::IsNullOrWhiteSpace(query)) {
            if (!recentSearches->Contains(query)) {
                if (recentSearches->Count >= 10)
                    recentSearches->RemoveAt(0);
                recentSearches->Add(query);
            }
        }
    }

    static array<String^>^ GetRecents()
    {
        return recentSearches->ToArray();
    }

    static DataTable^ GetAllEmployeesSorted(String^ sortByColumn) {
        if (String::IsNullOrWhiteSpace(sortByColumn))
            sortByColumn = "EmployeeID";  

        DataTable^ table = gcnew DataTable();

        try {
            SqlConnection^ con = gcnew SqlConnection(connectionString);
            con->Open();

            if (sortByColumn != "EmployeeID" && sortByColumn != "Position" && sortByColumn != "FullName") {
                sortByColumn = "EmployeeID";
            }

            String^ query = "SELECT * FROM dbo.Employees ORDER BY " + sortByColumn + " ASC";
            SqlDataAdapter^ adapter = gcnew SqlDataAdapter(query, con);
            adapter->Fill(table);

            con->Close();
        }
        catch (Exception^ ex) {
            System::Windows::Forms::MessageBox::Show(
                "Error sorting employees: " + ex->Message,
                "Error",
                System::Windows::Forms::MessageBoxButtons::OK,
                System::Windows::Forms::MessageBoxIcon::Error
            );
        }

        return table;
    }

};
