#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>

// -------------------------
// Utility for showing errors
// -------------------------
void showError(SQLHANDLE handle, SQLSMALLINT type, const std::string& msg) {
    SQLWCHAR sqlState[1024];
    SQLWCHAR message[1024];
    
    if (SQLGetDiagRecW(type, handle, 1, sqlState, NULL, message, 1024, NULL) == SQL_SUCCESS) {
        std::wcerr << L"[ERROR] " << std::wstring(msg.begin(), msg.end())
            << L" - SQLState: " << sqlState
            << L" Message: " << message << std::endl;
    }
}
// -------------------------
// Execute SQL command
// -------------------------
bool executeQuery(SQLHSTMT hStmt, const std::wstring& query) {
    SQLRETURN ret = SQLExecDirectW(hStmt, (SQLWCHAR*)query.c_str(), SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        showError(hStmt, SQL_HANDLE_STMT, "Failed to execute query");
        return false;
    }
    SQLCloseCursor(hStmt);
    return true;
}

// -------------------------
// Get latest inserted ID
// -------------------------
int getLastID(SQLHSTMT hStmt) {
    SQLRETURN ret;
    SQLINTEGER id = 0;
    SQLLEN cbID = 0;

    SQLWCHAR query[] = L"SELECT SCOPE_IDENTITY();";
    ret = SQLExecDirectW(hStmt, query, SQL_NTS);

    if (SQL_SUCCEEDED(ret)) {
        SQLBindCol(hStmt, 1, SQL_C_SLONG, &id, 0, &cbID);
        if (SQLFetch(hStmt) == SQL_SUCCESS) {
            SQLCloseCursor(hStmt);
            return id;
        }
    }

    SQLCloseCursor(hStmt);
    return 0;
}

// -------------------------
// Insert employee
// -------------------------
bool insertEmployee(SQLHSTMT hStmt, const std::wstring& name, const std::wstring& position, int weight, int parentID) {
    std::wstring query = L"INSERT INTO dbo.Employees (FullName, Position, Weight, ParentID) VALUES (N'" +
        name + L"', N'" + position + L"', " + std::to_wstring(weight) + L", " + std::to_wstring(parentID) + L");";
    return executeQuery(hStmt, query);
}

// -------------------------
// Main
// -------------------------
int main() {
    SQLHENV hEnv = NULL;
    SQLHDBC hDbc = NULL;
    SQLHSTMT hStmt = NULL;
    SQLRETURN ret;

    // Initialize ODBC
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
    SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

    // Connection string (wide)
    SQLWCHAR connStr[] =
        L"Driver={ODBC Driver 17 for SQL Server};Server=ALVINJOHNDANO\\SQLEXPRESS;"
        L"Database=LPO_DSA;Trusted_Connection=Yes;Encrypt=Yes;TrustServerCertificate=Yes;";

    // Connect
    ret = SQLDriverConnectW(hDbc, NULL, connStr, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT);
    if (!SQL_SUCCEEDED(ret)) {
        showError(hDbc, SQL_HANDLE_DBC, "Failed to connect to database");
        return -1;
    }
    std::cout << "[OK] Connected to SQL Server successfully.\n";

    // Allocate statement
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    // -------------------------
    // Data generation
    // -------------------------
    std::vector<std::wstring> names = {
        L"Alice", L"Bob", L"Charlie", L"Diana", L"Ethan", L"Fiona", L"George", L"Hannah",
        L"Ivan", L"Julia", L"Kevin", L"Laura", L"Mike", L"Nina", L"Oscar", L"Paula",
        L"Quincy", L"Rachel", L"Sam", L"Tina", L"Uma", L"Victor", L"Wendy", L"Xavier", L"Yara", L"Zane"
    };

    int ownerID = 0;
    int ceoIDs[5];
    int managerIDs[10];

    // Insert Owner
    insertEmployee(hStmt, L"Owner Alpha", L"Owner", 0, 0);
    ownerID = getLastID(hStmt);

    // Insert 5 CEOs (parent = Owner)
    for (int i = 0; i < 5; ++i) {
        std::wstring name = names[i] + L" CEO";
        insertEmployee(hStmt, name, L"CEO", 1, ownerID);
        ceoIDs[i] = getLastID(hStmt);
    }

    // Insert 10 Managers (2 per CEO)
    int m = 0;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 2; ++j) {
            std::wstring name = names[m + 5] + L" Manager";
            insertEmployee(hStmt, name, L"Manager", 2, ceoIDs[i]);
            managerIDs[m] = getLastID(hStmt);
            m++;
        }
    }

    // Insert 50 Employees (5 per Manager)
    int nameIdx = 0;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 5; ++j) {
            std::wstring name = names[nameIdx % names.size()] + L" Employee";
            insertEmployee(hStmt, name, L"Employee", 3, managerIDs[i]);
            nameIdx++;
        }
    }

    std::cout << "[OK] Data generation and insertion completed.\n";

    // Cleanup
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    SQLDisconnect(hDbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

    return 0;
}
