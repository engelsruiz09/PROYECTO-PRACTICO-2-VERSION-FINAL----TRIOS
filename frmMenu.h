#pragma once
#include "frmAlumnos.h"
#include "frmDocente.h"
#include "frmEmpleado.h"
#include "frmPersonas.h"
#include "frmReportes.h"

namespace PROYECTOPRACTICO2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de MyForm
	/// </summary>
	public ref class frmMenu : public System::Windows::Forms::Form
	{
	public:
		frmMenu(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~frmMenu()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ btnAlumnos;
	private: System::Windows::Forms::Button^ btnDocentes;
	private: System::Windows::Forms::Button^ btnEmpleados;
	private: System::Windows::Forms::Button^ btnPersonas;
	private: System::Windows::Forms::Button^ btnReportes;
	protected:

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(frmMenu::typeid));
			this->btnAlumnos = (gcnew System::Windows::Forms::Button());
			this->btnDocentes = (gcnew System::Windows::Forms::Button());
			this->btnEmpleados = (gcnew System::Windows::Forms::Button());
			this->btnPersonas = (gcnew System::Windows::Forms::Button());
			this->btnReportes = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// btnAlumnos
			// 
			this->btnAlumnos->BackColor = System::Drawing::Color::LightBlue;
			this->btnAlumnos->Location = System::Drawing::Point(13, 13);
			this->btnAlumnos->Margin = System::Windows::Forms::Padding(4);
			this->btnAlumnos->Name = L"btnAlumnos";
			this->btnAlumnos->Size = System::Drawing::Size(481, 68);
			this->btnAlumnos->TabIndex = 0;
			this->btnAlumnos->Text = L"Alumnos";
			this->btnAlumnos->UseVisualStyleBackColor = false;
			this->btnAlumnos->Click += gcnew System::EventHandler(this, &frmMenu::btnAlumnos_Click);
			// 
			// btnDocentes
			// 
			this->btnDocentes->BackColor = System::Drawing::Color::LightBlue;
			this->btnDocentes->Location = System::Drawing::Point(13, 99);
			this->btnDocentes->Margin = System::Windows::Forms::Padding(4);
			this->btnDocentes->Name = L"btnDocentes";
			this->btnDocentes->Size = System::Drawing::Size(481, 68);
			this->btnDocentes->TabIndex = 1;
			this->btnDocentes->Text = L"Docentes";
			this->btnDocentes->UseVisualStyleBackColor = false;
			this->btnDocentes->Click += gcnew System::EventHandler(this, &frmMenu::btnDocentes_Click);
			// 
			// btnEmpleados
			// 
			this->btnEmpleados->BackColor = System::Drawing::Color::LightBlue;
			this->btnEmpleados->Location = System::Drawing::Point(13, 187);
			this->btnEmpleados->Margin = System::Windows::Forms::Padding(4);
			this->btnEmpleados->Name = L"btnEmpleados";
			this->btnEmpleados->Size = System::Drawing::Size(481, 68);
			this->btnEmpleados->TabIndex = 2;
			this->btnEmpleados->Text = L"Empleados";
			this->btnEmpleados->UseVisualStyleBackColor = false;
			this->btnEmpleados->Click += gcnew System::EventHandler(this, &frmMenu::btnEmpleados_Click);
			// 
			// btnPersonas
			// 
			this->btnPersonas->BackColor = System::Drawing::Color::LightBlue;
			this->btnPersonas->Location = System::Drawing::Point(13, 274);
			this->btnPersonas->Margin = System::Windows::Forms::Padding(4);
			this->btnPersonas->Name = L"btnPersonas";
			this->btnPersonas->Size = System::Drawing::Size(481, 68);
			this->btnPersonas->TabIndex = 3;
			this->btnPersonas->Text = L"Personas";
			this->btnPersonas->UseVisualStyleBackColor = false;
			this->btnPersonas->Click += gcnew System::EventHandler(this, &frmMenu::btnPersonas_Click);
			// 
			// btnReportes
			// 
			this->btnReportes->BackColor = System::Drawing::Color::LightBlue;
			this->btnReportes->Location = System::Drawing::Point(13, 366);
			this->btnReportes->Margin = System::Windows::Forms::Padding(4);
			this->btnReportes->Name = L"btnReportes";
			this->btnReportes->Size = System::Drawing::Size(481, 68);
			this->btnReportes->TabIndex = 4;
			this->btnReportes->Text = L"Reportes";
			this->btnReportes->UseVisualStyleBackColor = false;
			this->btnReportes->Click += gcnew System::EventHandler(this, &frmMenu::btnReportes_Click);
			// 
			// frmMenu
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 19);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(513, 447);
			this->Controls->Add(this->btnReportes);
			this->Controls->Add(this->btnPersonas);
			this->Controls->Add(this->btnEmpleados);
			this->Controls->Add(this->btnDocentes);
			this->Controls->Add(this->btnAlumnos);
			this->Font = (gcnew System::Drawing::Font(L"Century Gothic", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(6);
			this->Name = L"frmMenu";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Menu";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void btnAlumnos_Click(System::Object^ sender, System::EventArgs^ e)
	{
		frmAlumnos^ frmuno = gcnew frmAlumnos();
		frmuno->ShowDialog();
	}
	private: System::Void btnDocentes_Click(System::Object^ sender, System::EventArgs^ e)
	{
		frmDocente^ frmdos = gcnew frmDocente();
		frmdos->ShowDialog();
	}
	private: System::Void btnEmpleados_Click(System::Object^ sender, System::EventArgs^ e) {
		frmEmpleado^ frmtres = gcnew frmEmpleado();
		frmtres->ShowDialog();
	}
	private: System::Void btnPersonas_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		frmPersonas^ frmtres = gcnew frmPersonas();
		frmtres->ShowDialog();
	}
	private: System::Void btnReportes_Click(System::Object^ sender, System::EventArgs^ e)
	{
		frmReportes^ frmcuatro = gcnew frmReportes();
		frmcuatro->ShowDialog();
	}
};
}
