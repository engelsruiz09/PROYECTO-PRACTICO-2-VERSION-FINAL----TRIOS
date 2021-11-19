#pragma once
#include "Alumno.h"
#include "Docente.h"
#include "Lista.h"

namespace PROYECTOPRACTICO2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class frmReportes : public System::Windows::Forms::Form
	{
		std::string StdString(System::String^ text)
		{
			return msclr::interop::marshal_as<std::string>(text);
		}
		System::String^ VisualString(std::string text)
		{
			return gcnew System::String(text.c_str());
		}
		Lista<Alumno*>* alumnos;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
		   Lista<Docente*>* docentes;
	public:
		frmReportes(void)
		{
			InitializeComponent();
			alumnos = new Lista<Alumno*>();
			docentes = new Lista<Docente*>();
			LeerCSVEstudiantes();
			LeerCSVDocentes();
		}

	protected:
		~frmReportes()
		{
			if (components)
			{
				delete components;
			}
		}
		void LeerCSVEstudiantes()
		{
			CsvReader* CSV = new CsvReader("data/estudiantes1.csv");
			while (CSV->ReadLine())
			{
				Alumno* alumno = new Alumno();
				CSV->Read(alumno->Apellidos);
				CSV->Read(alumno->Nombres);
				std::string ingreso;
				CSV->Read(ingreso);
				alumno->Ingreso = std::stoi(ingreso);
				CSV->Read(alumno->DPI);
				CSV->Read(alumno->Facultad);
				CSV->Read(alumno->Modalida);

				std::string str_curso;
				while (CSV->Read(str_curso))
				{
					String^ CURSO = VisualString(str_curso);

					Curso* curso = new Curso();
					curso->Nombre = StdString(CURSO->Split(' ')[0]);
					curso->Nota = std::stof(StdString(CURSO->Split(' ')[1]));

					alumno->Cursos->Insertar(curso);
				}

				alumnos->Insertar(alumno);
			}
		}
		void LeerCSVDocentes()
		{
			CsvReader* CSV = new CsvReader("data/trabajadores1.csv");
			while (CSV->ReadLine())
			{
				std::string data;
				Docente* docente = new Docente();
				CSV->Read(docente->Apellidos);
				CSV->Read(docente->Nombres);
				CSV->Read(docente->DPI);
				CSV->Read(data); docente->Inicio = std::stoi(data);
				CSV->Read(data); docente->Salario = std::stof(data);
				CSV->Read(data); //Tipo true->Docente  false->Trabajador
				if (data == "true")
				{
					std::string str_curso;
					while (CSV->Read(str_curso))
					{
						Curso* curso = new Curso();
						curso->Nombre = str_curso;
						docente->Cursos->Insertar(curso);
					}
					docentes->Insertar(docente);
				}
				else
					delete docente;
			}
		}
	private: System::Windows::Forms::TextBox^ textBox1;
	protected:
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ListBox^ lbxAlumnos;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::ListBox^ lbxProfesores;
	private: System::Windows::Forms::Label^ lblCantAlumnos;
	private: System::Windows::Forms::Label^ lblCantProfesores;

	private: System::ComponentModel::Container ^components;

	#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(frmReportes::typeid));
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->lbxAlumnos = (gcnew System::Windows::Forms::ListBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->lbxProfesores = (gcnew System::Windows::Forms::ListBox());
			this->lblCantAlumnos = (gcnew System::Windows::Forms::Label());
			this->lblCantProfesores = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(90, 12);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(459, 27);
			this->textBox1->TabIndex = 0;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &frmReportes::textBox1_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 15);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(56, 19);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Curso:";
			// 
			// lbxAlumnos
			// 
			this->lbxAlumnos->FormattingEnabled = true;
			this->lbxAlumnos->ItemHeight = 19;
			this->lbxAlumnos->Location = System::Drawing::Point(12, 94);
			this->lbxAlumnos->Name = L"lbxAlumnos";
			this->lbxAlumnos->Size = System::Drawing::Size(252, 365);
			this->lbxAlumnos->TabIndex = 2;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 68);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(81, 19);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Alumnos:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(297, 68);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(88, 19);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Profesores:";
			// 
			// lbxProfesores
			// 
			this->lbxProfesores->FormattingEnabled = true;
			this->lbxProfesores->ItemHeight = 19;
			this->lbxProfesores->Location = System::Drawing::Point(297, 94);
			this->lbxProfesores->Name = L"lbxProfesores";
			this->lbxProfesores->Size = System::Drawing::Size(252, 403);
			this->lbxProfesores->TabIndex = 4;
			// 
			// lblCantAlumnos
			// 
			this->lblCantAlumnos->AutoSize = true;
			this->lblCantAlumnos->Location = System::Drawing::Point(221, 68);
			this->lblCantAlumnos->Name = L"lblCantAlumnos";
			this->lblCantAlumnos->Size = System::Drawing::Size(36, 19);
			this->lblCantAlumnos->TabIndex = 6;
			this->lblCantAlumnos->Text = L"000";
			this->lblCantAlumnos->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// lblCantProfesores
			// 
			this->lblCantProfesores->AutoSize = true;
			this->lblCantProfesores->Location = System::Drawing::Point(506, 68);
			this->lblCantProfesores->Name = L"lblCantProfesores";
			this->lblCantProfesores->Size = System::Drawing::Size(36, 19);
			this->lblCantProfesores->TabIndex = 7;
			this->lblCantProfesores->Text = L"000";
			this->lblCantProfesores->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 473);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(114, 38);
			this->button1->TabIndex = 8;
			this->button1->Text = L"Nombre";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &frmReportes::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(150, 473);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(114, 38);
			this->button2->TabIndex = 9;
			this->button2->Text = L"Nota";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &frmReportes::button2_Click);
			// 
			// frmReportes
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 19);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(561, 523);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->lblCantProfesores);
			this->Controls->Add(this->lblCantAlumnos);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->lbxProfesores);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->lbxAlumnos);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Font = (gcnew System::Drawing::Font(L"Century Gothic", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"frmReportes";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"frmReportes";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
	#pragma endregion
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		lbxAlumnos->Items->Clear();
		for (int i = 0; i < alumnos->cantidad; i++)
		{
			Alumno* alumno = alumnos->Obtener(i);
			
			for (int j = 0; j < alumno->Cursos->cantidad; j++)
			{
				Curso* curso = alumno->Cursos->Obtener(j);
				if (curso->Nombre == StdString(textBox1->Text))
				{
					lbxAlumnos->Items->Add(curso->Nota + VisualString(" | " + alumno->Nombres + " " + alumno->Apellidos));
					break;
				}
			}				
		}
		lblCantAlumnos->Text = lbxAlumnos->Items->Count.ToString();

		lbxProfesores->Items->Clear();
		for (int i = 0; i < docentes->cantidad; i++)
		{
			Docente* docente = docentes->Obtener(i);

			for (int j = 0; j < docente->Cursos->cantidad; j++)
			{
				Curso* curso = docente->Cursos->Obtener(j);
				if (curso->Nombre == StdString(textBox1->Text))
				{
					lbxProfesores->Items->Add(VisualString(docente->Nombres + " " + docente->Apellidos));
					break;
				}
			}				
		}
		lblCantProfesores->Text = lbxProfesores->Items->Count.ToString();
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		for (int i = 0; i < lbxAlumnos->Items->Count - 1; i++)
			for (int j = i + 1; j < lbxAlumnos->Items->Count; j++)
			{
				String^ valor1 = lbxAlumnos->Items[i]->ToString();
				String^ valor2 = lbxAlumnos->Items[j]->ToString();

				String^ nombre1 = valor1->Split('|')[1];
				String^ nombre2 = valor2->Split('|')[1];

				if (StdString(nombre1) > StdString(nombre2))
				{
					lbxAlumnos->Items->RemoveAt(i);
					lbxAlumnos->Items->Insert(i, valor2);

					lbxAlumnos->Items->RemoveAt(j);
					lbxAlumnos->Items->Insert(j, valor1);
				}
			}
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e)
	{
		for (int i = 0; i < lbxAlumnos->Items->Count - 1; i++)
			for (int j = i + 1; j < lbxAlumnos->Items->Count; j++)
			{
				String^ valor1 = lbxAlumnos->Items[i]->ToString();
				String^ valor2 = lbxAlumnos->Items[j]->ToString();

				int nota1 = Convert::ToInt32( valor1->Split('|')[0]->Trim() );//para quitar el espacio que tiene entre la barraxd y la nota
				int nota2 = Convert::ToInt32( valor2->Split('|')[0]->Trim() );

				if (nota1 > nota2)
				{
					lbxAlumnos->Items->RemoveAt(i);
					lbxAlumnos->Items->Insert(i, valor2);

					lbxAlumnos->Items->RemoveAt(j);
					lbxAlumnos->Items->Insert(j, valor1);
				}
			}
	}
};
}
