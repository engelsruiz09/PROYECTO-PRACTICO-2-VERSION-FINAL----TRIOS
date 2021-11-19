#pragma once
#include "Persona.h"
#include "Lista.h"
#include "CsvReader.h"

namespace PROYECTOPRACTICO2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class frmPersonas : public System::Windows::Forms::Form
	{
		std::string StdString(System::String^ text)
		{
			return msclr::interop::marshal_as<std::string>(text);
		}
		System::String^ VisualString(std::string text)
		{
			return gcnew System::String(text.c_str());
		}
		Lista<Persona*>* personas;
	public:
		frmPersonas(void)
		{
			InitializeComponent();
			personas = new Lista<Persona*>();
			LeerCSV("data/estudiantes1.csv");
			LeerCSV("data/trabajadores1.csv");
		}
		void LeerCSV(std::string ruta)
		{
			CsvReader* CSV = new CsvReader(ruta);
			while (CSV->ReadLine())
			{
				std::string data;
				Persona* persona = new Persona();
				CSV->Read(persona->Apellidos);
				CSV->Read(persona->Nombres);
				CSV->Read(data);
				if (data.length() != 15)
					CSV->Read(data);
				persona->DPI = data;
				personas->Insertar(persona);
			}
		}

	protected:
		~frmPersonas()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ txtNombre;
	protected:

	protected:

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ lblNombre;

	protected:

	private: System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(frmPersonas::typeid));
			this->txtNombre = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->lblNombre = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// txtNombre
			// 
			this->txtNombre->Location = System::Drawing::Point(13, 34);
			this->txtNombre->Margin = System::Windows::Forms::Padding(4);
			this->txtNombre->Name = L"txtNombre";
			this->txtNombre->Size = System::Drawing::Size(488, 27);
			this->txtNombre->TabIndex = 0;
			this->txtNombre->TextChanged += gcnew System::EventHandler(this, &frmPersonas::textBox1_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(9, 7);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(37, 19);
			this->label1->TabIndex = 1;
			this->label1->Text = L"DPI:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(9, 80);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(77, 19);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Nombre:";
			// 
			// lblNombre
			// 
			this->lblNombre->AutoSize = true;
			this->lblNombre->Location = System::Drawing::Point(113, 80);
			this->lblNombre->Name = L"lblNombre";
			this->lblNombre->Size = System::Drawing::Size(0, 19);
			this->lblNombre->TabIndex = 3;
			// 
			// frmPersonas
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 19);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(514, 132);
			this->Controls->Add(this->lblNombre);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->txtNombre);
			this->DoubleBuffered = true;
			this->Font = (gcnew System::Drawing::Font(L"Century Gothic", 12, System::Drawing::FontStyle::Bold));
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"frmPersonas";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"frmPersonas";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e)
	{
		//aplicamos una busqueda lineal ya que como los datos no estan ordenados como tal
		for (int i = 0; i < personas->cantidad; i++)
		{
			Persona* persona = personas->Obtener(i);
			if (persona->DPI == StdString(txtNombre->Text))
			{
				lblNombre->Text = VisualString(persona->Nombres + " " + persona->Apellidos);
				break;
			}
			else
				lblNombre->Text = "No se encontraro registros";
				
		}
	}
};
}
