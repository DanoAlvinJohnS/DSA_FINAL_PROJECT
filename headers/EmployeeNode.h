#pragma once
using namespace System;
using namespace System::Collections::Generic;

public ref class EmployeeNode
{
public:
    String^ Name;
    String^ Position;
    int ID;
    EmployeeNode^ Parent;
    List<EmployeeNode^>^ Children;

    EmployeeNode(String^ name, String^ position, int id)
    {
        Name = name;
        Position = position;
        ID = id;
        Children = gcnew List<EmployeeNode^>();
        Parent = nullptr;
    }

    void AddChild(EmployeeNode^ child)
    {
        if (!Children->Contains(child))
        {
            Children->Add(child);
            child->Parent = this;
        }
    }
};
