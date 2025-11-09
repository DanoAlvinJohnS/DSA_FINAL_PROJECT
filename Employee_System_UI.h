#pragma once
#include "headers/Employee_Handler.h"
#include "EmployeeNode.h"

namespace DSAPROJECTFINALIZED {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Employee_System_UI
	/// </summary>
	public ref class Employee_System_UI : public System::Windows::Forms::Form
	{
	public:
		Employee_System_UI(void) {
		
			InitializeComponent();
			this->search_combo->TextChanged += gcnew System::EventHandler(this, &Employee_System_UI::search_combo_TextChanged);
			this->search_combo->SelectedIndexChanged += gcnew System::EventHandler(this, &Employee_System_UI::search_combo_SelectedIndexChanged);
			this->search_table->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Employee_System_UI::search_table_CellContentClick);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Employee_System_UI()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ exit_btn;
	protected:

	protected:

	protected:


	private:
		bool dragging;
		Point offset;

	private: System::Windows::Forms::ComboBox^ search_combo;

	private: System::Windows::Forms::DataGridView^ search_table;
	private: System::Windows::Forms::Button^ s_id;


	private: System::Windows::Forms::Button^ s_a;
	private: System::Windows::Forms::Button^ s_p;
	private: System::Windows::Forms::Button^ show_tree_btn;
	private: System::Windows::Forms::Button^ button1;







		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		/// 
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Employee_System_UI::typeid));
			this->exit_btn = (gcnew System::Windows::Forms::Button());
			this->search_combo = (gcnew System::Windows::Forms::ComboBox());
			this->search_table = (gcnew System::Windows::Forms::DataGridView());
			this->s_id = (gcnew System::Windows::Forms::Button());
			this->s_a = (gcnew System::Windows::Forms::Button());
			this->s_p = (gcnew System::Windows::Forms::Button());
			this->show_tree_btn = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->search_table))->BeginInit();
			this->SuspendLayout();
			// 
			// exit_btn
			// 
			this->exit_btn->Location = System::Drawing::Point(12, 12);
			this->exit_btn->Name = L"exit_btn";
			this->exit_btn->Size = System::Drawing::Size(28, 27);
			this->exit_btn->TabIndex = 0;
			this->exit_btn->Text = L"X";
			this->exit_btn->UseVisualStyleBackColor = true;
			this->exit_btn->Click += gcnew System::EventHandler(this, &Employee_System_UI::exit_btn_clk);
			// 
			// search_combo
			// 
			this->search_combo->ForeColor = System::Drawing::Color::Black;
			this->search_combo->FormattingEnabled = true;
			this->search_combo->Location = System::Drawing::Point(12, 56);
			this->search_combo->Name = L"search_combo";
			this->search_combo->Size = System::Drawing::Size(678, 21);
			this->search_combo->TabIndex = 1;
			this->search_combo->SelectedIndexChanged += gcnew System::EventHandler(this, &Employee_System_UI::search_combo_SelectedIndexChanged);
			// 
			// search_table
			// 
			this->search_table->AllowUserToAddRows = false;
			this->search_table->AllowUserToDeleteRows = false;
			this->search_table->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->search_table->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
			this->search_table->BackgroundColor = System::Drawing::Color::PaleGreen;
			this->search_table->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->search_table->GridColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->search_table->Location = System::Drawing::Point(12, 112);
			this->search_table->Name = L"search_table";
			this->search_table->ReadOnly = true;
			this->search_table->RowHeadersVisible = false;
			this->search_table->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::AutoSizeToAllHeaders;
			this->search_table->Size = System::Drawing::Size(678, 288);
			this->search_table->TabIndex = 2;
			this->search_table->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Employee_System_UI::search_table_CellContentClick);
			// 
			// s_id
			// 
			this->s_id->Location = System::Drawing::Point(12, 83);
			this->s_id->Name = L"s_id";
			this->s_id->Size = System::Drawing::Size(150, 23);
			this->s_id->TabIndex = 3;
			this->s_id->Text = L"Sort by ID";
			this->s_id->UseVisualStyleBackColor = true;
			this->s_id->Click += gcnew System::EventHandler(this, &Employee_System_UI::s_id_Click);
			// 
			// s_a
			// 
			this->s_a->Location = System::Drawing::Point(284, 83);
			this->s_a->Name = L"s_a";
			this->s_a->Size = System::Drawing::Size(150, 23);
			this->s_a->TabIndex = 5;
			this->s_a->Text = L"Sort by Alphabetically";
			this->s_a->UseVisualStyleBackColor = true;
			this->s_a->Click += gcnew System::EventHandler(this, &Employee_System_UI::s_a_Click);
			// 
			// s_p
			// 
			this->s_p->Location = System::Drawing::Point(540, 83);
			this->s_p->Name = L"s_p";
			this->s_p->Size = System::Drawing::Size(150, 23);
			this->s_p->TabIndex = 6;
			this->s_p->Text = L"Sort by Position";
			this->s_p->UseVisualStyleBackColor = true;
			this->s_p->Click += gcnew System::EventHandler(this, &Employee_System_UI::s_p_Click);
			// 
			// show_tree_btn
			// 
			this->show_tree_btn->Location = System::Drawing::Point(296, 460);
			this->show_tree_btn->Name = L"show_tree_btn";
			this->show_tree_btn->Size = System::Drawing::Size(75, 23);
			this->show_tree_btn->TabIndex = 7;
			this->show_tree_btn->Text = L"button1";
			this->show_tree_btn->UseVisualStyleBackColor = true;
			this->show_tree_btn->Click += gcnew System::EventHandler(this, &Employee_System_UI::show_tree_btn_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(436, 460);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 8;
			this->button1->Text = L"view_branch_button";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Employee_System_UI::button1_Click);
			// 
			// Employee_System_UI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Honeydew;
			this->ClientSize = System::Drawing::Size(702, 555);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->show_tree_btn);
			this->Controls->Add(this->s_p);
			this->Controls->Add(this->s_a);
			this->Controls->Add(this->s_id);
			this->Controls->Add(this->search_table);
			this->Controls->Add(this->search_combo);
			this->Controls->Add(this->exit_btn);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"Employee_System_UI";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Employee_System_UI";
			this->Load += gcnew System::EventHandler(this, &Employee_System_UI::Employee_System_UI_Load);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Employee_System_UI::Employee_System_UI_MouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Employee_System_UI::Employee_System_UI_MouseMove);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Employee_System_UI::Employee_System_UI_MouseUp);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->search_table))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void Employee_System_UI_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		dragging = true;
		offset = Point(e->X, e->Y);
	}

	private: System::Void Employee_System_UI_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (dragging) {

			Point currentScreenPos = PointToScreen(Point(e->X, e->Y));
			this->Location = Point(currentScreenPos.X - offset.X, currentScreenPos.Y - offset.Y);
		}
	}

	private: System::Void Employee_System_UI_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		dragging = false;
	}

	private: System::Void Employee_System_UI_Load(System::Object^ sender, System::EventArgs^ e) {

	}

	private: System::Void exit_btn_clk(System::Object^ sender, System::EventArgs^ e) {
		if (MessageBox::Show("Are you sure you want to exit?", "Confirm Exit",
			MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
			Application::Exit();
		
	}

	private: System::Void search_table_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {

	}
	
	private: System::Void search_combo_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void search_combo_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		String^ query = search_combo->Text;

		DataTable^ results;
		if (String::IsNullOrWhiteSpace(query)) {
			results = EmployeeHandler::GetAllEmployeesSorted(); 
		}
		else {
		
			results = EmployeeHandler::SearchEmployees(query);
		}

		search_table->DataSource = results;

		search_table->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
		search_table->AutoSizeRowsMode = DataGridViewAutoSizeRowsMode::AllCells;
		search_table->DefaultCellStyle->WrapMode = DataGridViewTriState::False;
		search_table->RowHeadersVisible = false;

		search_combo->Items->Clear();
		array<String^>^ recents = EmployeeHandler::GetRecents();
		for each(String ^ item in recents)
		{
			if (item->ToLower()->Contains(query->ToLower()))
				search_combo->Items->Add(item);
		}

		search_combo->DroppedDown = true;
		search_combo->SelectionStart = search_combo->Text->Length;
	}



private: System::Void s_p_Click(System::Object^ sender, System::EventArgs^ e) {
	DataTable^ results = EmployeeHandler::GetAllEmployeesSorted("Position");
	search_table->DataSource = results;	

}
private: System::Void s_a_Click(System::Object^ sender, System::EventArgs^ e) {
	DataTable^ results = EmployeeHandler::GetAllEmployeesSorted("FullName");
	search_table->DataSource = results;
}
private: System::Void s_id_Click(System::Object^ sender, System::EventArgs^ e) {
	DataTable^ results = EmployeeHandler::GetAllEmployeesSorted("EmployeeID");
	search_table->DataSource = results;
}

private: System::Void show_tree_btn_Click(System::Object^ sender, System::EventArgs^ e) {
	EmployeeHandler^ handler = gcnew EmployeeHandler();
	handler->ShowEmployeeHierarchy();
}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
