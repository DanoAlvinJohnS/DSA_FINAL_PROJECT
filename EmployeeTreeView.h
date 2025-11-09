#pragma once
#include "EmployeeNode.h"

namespace DSAPROJECTFINALIZED {

    using namespace System;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::Drawing::Drawing2D;

    // Subclass Panel to allow DoubleBuffered drawing
    ref class DoubleBufferedPanel : public Panel
    {
    public:
        DoubleBufferedPanel()
        {
            this->SetStyle(ControlStyles::DoubleBuffer | ControlStyles::UserPaint | ControlStyles::AllPaintingInWmPaint, true);
            this->UpdateStyles();
        }
    };

    public ref class EmployeeTreeView : public Form
    {
    private:
        DoubleBufferedPanel^ canvas;
        List<EmployeeNode^>^ displayRoots;
        List<EmployeeNode^>^ highlightedNodes;

        float zoomFactor = 1.0f;
        Point panOffset;
        bool isPanning = false;
        Point lastMousePos;

        // Layout
        int boxWidth = 120;
        int boxHeight = 50;
        int horizontalSpacing = 40;
        int verticalSpacing = 80;
        int rootSpacing = 200;

    public:
        EmployeeTreeView(List<EmployeeNode^>^ roots)
        {
            displayRoots = roots;
            highlightedNodes = gcnew List<EmployeeNode^>();
            InitializeComponent();
        }

    private:
        void InitializeComponent(void)
        {
            this->Text = "Employee Hierarchy Tree";
            this->ClientSize = Drawing::Size(1200, 800);
            this->StartPosition = FormStartPosition::CenterScreen;

            canvas = gcnew DoubleBufferedPanel();
            canvas->Dock = DockStyle::Fill;
            canvas->BackColor = Color::White;
            canvas->MouseWheel += gcnew MouseEventHandler(this, &EmployeeTreeView::OnMouseWheelZoom);
            canvas->MouseDown += gcnew MouseEventHandler(this, &EmployeeTreeView::OnMouseDown);
            canvas->MouseUp += gcnew MouseEventHandler(this, &EmployeeTreeView::OnMouseUp);
            canvas->MouseMove += gcnew MouseEventHandler(this, &EmployeeTreeView::OnMouseMove);
            canvas->Paint += gcnew PaintEventHandler(this, &EmployeeTreeView::OnPaintTree);
            this->Controls->Add(canvas);
        }

        // Zoom with mouse wheel
        void OnMouseWheelZoom(System::Object^ sender, MouseEventArgs^ e)
        {
            float oldZoom = zoomFactor;
            if (e->Delta > 0) zoomFactor *= 1.1f;
            else zoomFactor /= 1.1f;

            // Optional: zoom to mouse position
            float dx = (float)e->X - panOffset.X;
            float dy = (float)e->Y - panOffset.Y;

            panOffset.X -= (int)(dx * (zoomFactor / oldZoom - 1));
            panOffset.Y -= (int)(dy * (zoomFactor / oldZoom - 1));

            canvas->Invalidate();
        }

        // Panning support
        void OnMouseDown(System::Object^ sender, MouseEventArgs^ e)
        {
            if (e->Button == System::Windows::Forms::MouseButtons::Left)
            {
                isPanning = true;
                lastMousePos = e->Location;
            }
        }

        void OnMouseUp(System::Object^ sender, MouseEventArgs^ e)
        {
            isPanning = false;
        }

        void OnMouseMove(System::Object^ sender, MouseEventArgs^ e)
        {
            if (isPanning)
            {
                panOffset.X += e->X - lastMousePos.X;
                panOffset.Y += e->Y - lastMousePos.Y;
                lastMousePos = e->Location;
                canvas->Invalidate();
            }
        }

        void OnPaintTree(System::Object^ sender, PaintEventArgs^ e)
        {
            Graphics^ g = e->Graphics;
            g->SmoothingMode = SmoothingMode::HighQuality;

            // Apply pan and zoom
            g->TranslateTransform((float)panOffset.X, (float)panOffset.Y);
            g->ScaleTransform(zoomFactor, zoomFactor);

            if (displayRoots == nullptr || displayRoots->Count == 0)
                return;

            int totalWidth = (displayRoots->Count - 1) * (boxWidth + rootSpacing);
            int startX = (canvas->ClientSize.Width / 2) - totalWidth / 2;
            int y = 30;

            for (int i = 0; i < displayRoots->Count; i++)
            {
                int x = startX + i * (boxWidth + rootSpacing);
                DrawNode(g, displayRoots[i], x, y);
            }
        }

        void DrawNode(Graphics^ g, EmployeeNode^ node, int x, int y)
        {
            Rectangle rect(x - boxWidth / 2, y, boxWidth, boxHeight);

            Brush^ brush = highlightedNodes->Contains(node) ? Brushes::Orange : Brushes::LightBlue;

            g->FillRectangle(brush, rect);
            g->DrawRectangle(Pens::SteelBlue, rect);

            StringFormat^ sf = gcnew StringFormat();
            sf->Alignment = StringAlignment::Center;
            sf->LineAlignment = StringAlignment::Center;
            g->DrawString(node->Name + "\n" + node->Position,
                gcnew System::Drawing::Font("Segoe UI", 9),
                Brushes::Black, rect, sf);

            if (node->Children == nullptr || node->Children->Count == 0)
                return;

            int totalWidth = 0;
            array<int>^ childWidths = gcnew array<int>(node->Children->Count);

            for (int i = 0; i < node->Children->Count; i++)
            {
                childWidths[i] = CalculateSubtreeWidth(node->Children[i]);
                totalWidth += childWidths[i];
                if (i < node->Children->Count - 1)
                    totalWidth += horizontalSpacing;
            }

            int startX = x - totalWidth / 2;
            int childX = startX;

            for (int i = 0; i < node->Children->Count; i++)
            {
                EmployeeNode^ child = node->Children[i];
                int cx = childX + childWidths[i] / 2;
                int cy = y + boxHeight + verticalSpacing;

                g->DrawLine(Pens::Gray, x, y + boxHeight, cx, cy);
                DrawNode(g, child, cx, cy);

                childX += childWidths[i] + horizontalSpacing;
            }
        }

        int CalculateSubtreeWidth(EmployeeNode^ node)
        {
            if (node->Children == nullptr || node->Children->Count == 0)
                return boxWidth;

            int totalWidth = 0;
            for each(EmployeeNode ^ child in node->Children)
            {
                totalWidth += CalculateSubtreeWidth(child) + horizontalSpacing;
            }
            totalWidth -= horizontalSpacing; // remove extra spacing
            return totalWidth;
        }

        // Highlight nodes by search query
        void HighlightNodes(String^ query)
        {
            highlightedNodes->Clear();
            if (String::IsNullOrWhiteSpace(query))
                return;

            for each(EmployeeNode ^ root in displayRoots)
                HighlightNodesRecursive(root, query);
            canvas->Invalidate();
        }

        void HighlightNodesRecursive(EmployeeNode^ node, String^ query)
        {
            if (node->Name->ToLower()->Contains(query->ToLower()) ||
                node->Position->ToLower()->Contains(query->ToLower()) ||
                node->ID.ToString()->Contains(query))
            {
                highlightedNodes->Add(node);
            }

            if (node->Children != nullptr)
                for each(EmployeeNode ^ child in node->Children)
                    HighlightNodesRecursive(child, query);
        }

        // Show only branch (selected node + parents)
        void ShowBranch(EmployeeNode^ node)
        {
            List<EmployeeNode^>^ branchRoots = gcnew List<EmployeeNode^>();
            EmployeeNode^ current = node;
            EmployeeNode^ prev = nullptr;

            while (current != nullptr)
            {
                EmployeeNode^ copy = gcnew EmployeeNode(current->Name, current->Position, current->ID);
                if (prev != nullptr)
                    copy->AddChild(prev);

                prev = copy;
                current = current->Parent; 
            }

            branchRoots->Add(prev);
            displayRoots = branchRoots;
            canvas->Invalidate();
        }
    };
}
