#include <iostream>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include "headers/EmployeeGenerator.h"
#include "Employee_System_UI.h"

using namespace System;
using namespace DSAPROJECTFINALIZED;

[STAThreadAttribute]

int main() {
    EmployeeGenerator gen;
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    Employee_System_UI^ form = gcnew Employee_System_UI();
    Application::Run(form);
    return 0;
}
