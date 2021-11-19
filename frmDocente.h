#pragma once
#include "Lista.h";
#include "Docente.h";
#include "CsvReader.h";

namespace PROYECTOPRACTICO2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class frmDocente : public System::Windows::Forms::Form
	{
		std::string StdString(System::String^ text)
		{
			return msclr::interop::marshal_as<std::string>(text);
		}
		System::String^ VisualString(std::string text)
		{
			return gcnew System::String(text.c_str());
		}
		Lista<Docente*>* docentes;
		Lista<Curso*>* cursos;
	private: System::Windows::Forms::NumericUpDown^ nudCrearSalario;

	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::NumericUpDown^ nudModificarSalario;

	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Button^ btnModificarAgregarCurso;
	private: System::Windows::Forms::TabPage^ tabPage5;
	private: System::Windows::Forms::Label^ lblSalarioPromedio;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Button^ btnAbrir;
	private: System::Windows::Forms::OpenFileDialog^ ofdOpen;
		   Docente* docenteModificar = nullptr;

	public:
		frmDocente(void)
		{
			InitializeComponent();

			AgregarColumna("Codigo");
			AgregarColumna("Apellido");
			AgregarColumna("Nombre");
			AgregarColumna("DPI");
			AgregarColumna("Inicio");
			AgregarColumna("Salario");
			AgregarColumna("N° Cursos");


			docentes = new Lista<Docente*>;
			cursos = new Lista<Curso*>;
			LeerCSV("data/trabajadores1.csv");
			LlenarDatosDocentes();
		}

	protected:
		~frmDocente()
		{
			if (components)
			{
				delete components;
			}
		}
		void LeerCSV(String^ path)
		{
			docentes = new Lista<Docente*>;
			CsvReader* CSV = new CsvReader(StdString(path));
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

				//aca se genera los primeros 5 numeros aleatorio y se le concatena los ultimos dos del año de ingreso pero como es una fecha aplicamos lo siguieten ;s
				docente->Codigo = (rand() % (100000 - 10000) + 10000) * 100 + ((docente->Inicio / 10000) % 100);
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

		void AgregarColumna(String^ nombre)
		{
			DataGridViewColumn^ col = gcnew DataGridViewColumn();
			col->Width = 120;
			col->HeaderText = nombre;
			DataGridViewCell^ cellTemplate = gcnew DataGridViewTextBoxCell();
			col->CellTemplate = cellTemplate;
			dgvDatosDocentes->Columns->Add(col);
		}
		void LlenarDatosDocentes()
		{
			dgvDatosDocentes->Rows->Clear();
			for (int i = 0; i < docentes->cantidad; i++)
			{
				Docente* docente = docentes->Obtener(i);
				DataGridViewRow^ row = gcnew DataGridViewRow();

				DataGridViewCell^ cell = gcnew DataGridViewTextBoxCell();
				cell->Value = docente->Codigo;
				row->Cells->Add(cell);

				cell = gcnew DataGridViewTextBoxCell();
				cell->Value = VisualString(docente->Apellidos);
				row->Cells->Add(cell);

				cell = gcnew DataGridViewTextBoxCell();
				cell->Value = VisualString(docente->Nombres);
				row->Cells->Add(cell);

				cell = gcnew DataGridViewTextBoxCell();
				cell->Value = VisualString(docente->DPI);
				row->Cells->Add(cell);

				cell = gcnew DataGridViewTextBoxCell();
				cell->Value = docente->Inicio;
				row->Cells->Add(cell);

				cell = gcnew DataGridViewTextBoxCell();
				cell->Value = docente->Salario;
				row->Cells->Add(cell);

				cell = gcnew DataGridViewTextBoxCell();
				cell->Value = docente->Cursos->cantidad;
				row->Cells->Add(cell);

				dgvDatosDocentes->Rows->Add(row);
			}

			lbxBorrarDocentes->Items->Clear();
			for (int i = 0; i < docentes->cantidad; i++)
			{
				Docente* docente = docentes->Obtener(i);
				std::string texto = docente->Apellidos + " " + docente->Nombres + " " + docente->DPI;
				lbxBorrarDocentes->Items->Add(VisualString(texto));
			}

			cbxModificarDocentes->Items->Clear();
			for (int i = 0; i < docentes->cantidad; i++)
			{
				Docente* docente = docentes->Obtener(i);
				std::string texto = docente->Apellidos + " " + docente->Nombres + " " + docente->DPI;
				cbxModificarDocentes->Items->Add(VisualString(texto));
			}

			lbxCrearCursos->Items->Clear();
			for (int i = 0; i < cursos->cantidad; i++)
			{
				Curso* curso = cursos->Obtener(i);
				lbxCrearCursos->Items->Add(VisualString(curso->Nombre));
			}
			if (docenteModificar != nullptr)
			{
				lbxModificarCursos->Items->Clear();
				for (int i = 0; i < docenteModificar->Cursos->cantidad; i++)
				{
					Curso* curso = docenteModificar->Cursos->Obtener(i);
					lbxModificarCursos->Items->Add(VisualString(curso->Nombre));
				}
			}

			float salarios = 0;
			for (int i = 0; i < docentes->cantidad; i++)
			{
				Docente* docente = docentes->Obtener(i);
				salarios += docente->Salario;
			}
			salarios /= docentes->cantidad;
			lblSalarioPromedio->Text = salarios.ToString();

		}
	private: System::Windows::Forms::TabControl^ tabControl1;
	protected:
	private: System::Windows::Forms::TabPage^ tabPage2;
	private: System::Windows::Forms::DataGridView^ dgvDatosDocentes;
	private: System::Windows::Forms::Button^ btnDatosGuardar;

	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::TabPage^ tabPage1;
	private: System::Windows::Forms::Button^ btnCrearEliminarCurso;
	private: System::Windows::Forms::Button^ btnCrearRegistrar;
	private: System::Windows::Forms::Button^ btnCrearAgregarCurso;
	private: System::Windows::Forms::ListBox^ lbxCrearCursos;

	private: System::Windows::Forms::Label^ label8;

	private: System::Windows::Forms::TextBox^ txtCrearCurso;
	private: System::Windows::Forms::Label^ label7;
private: System::Windows::Forms::NumericUpDown^ nupCrearInicio;






	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TextBox^ txtCrearDPI;
	private: System::Windows::Forms::TextBox^ txtCrearApellidos;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ txtCrearNombres;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TabPage^ tabPage3;
	private: System::Windows::Forms::Label^ label21;
	private: System::Windows::Forms::ComboBox^ cbxModificarDocentes;
	private: System::Windows::Forms::Button^ btnModificarEliminarCurso;
	private: System::Windows::Forms::Button^ btnModificar;

	private: System::Windows::Forms::ListBox^ lbxModificarCursos;

	private: System::Windows::Forms::Label^ label13;

	private: System::Windows::Forms::TextBox^ txtModificarCurso;
	private: System::Windows::Forms::Label^ label14;
private: System::Windows::Forms::NumericUpDown^ nudModificarInicio;





	private: System::Windows::Forms::Label^ label17;
	private: System::Windows::Forms::TextBox^ txtModificarDPI;
	private: System::Windows::Forms::TextBox^ txtModificarApellidos;
	private: System::Windows::Forms::Label^ label18;
	private: System::Windows::Forms::Label^ label19;
	private: System::Windows::Forms::TextBox^ txtModificarNombres;
	private: System::Windows::Forms::Label^ label20;
	private: System::Windows::Forms::TabPage^ tabPage4;
	private: System::Windows::Forms::Button^ btnBorrar;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::ListBox^ lbxBorrarDocentes;

	private: System::ComponentModel::Container ^components;

	#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(frmDocente::typeid));
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->btnAbrir = (gcnew System::Windows::Forms::Button());
			this->dgvDatosDocentes = (gcnew System::Windows::Forms::DataGridView());
			this->btnDatosGuardar = (gcnew System::Windows::Forms::Button());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->nudCrearSalario = (gcnew System::Windows::Forms::NumericUpDown());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->btnCrearEliminarCurso = (gcnew System::Windows::Forms::Button());
			this->btnCrearRegistrar = (gcnew System::Windows::Forms::Button());
			this->btnCrearAgregarCurso = (gcnew System::Windows::Forms::Button());
			this->lbxCrearCursos = (gcnew System::Windows::Forms::ListBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->txtCrearCurso = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->nupCrearInicio = (gcnew System::Windows::Forms::NumericUpDown());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->txtCrearDPI = (gcnew System::Windows::Forms::TextBox());
			this->txtCrearApellidos = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->txtCrearNombres = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->btnModificarAgregarCurso = (gcnew System::Windows::Forms::Button());
			this->nudModificarSalario = (gcnew System::Windows::Forms::NumericUpDown());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->cbxModificarDocentes = (gcnew System::Windows::Forms::ComboBox());
			this->btnModificarEliminarCurso = (gcnew System::Windows::Forms::Button());
			this->btnModificar = (gcnew System::Windows::Forms::Button());
			this->lbxModificarCursos = (gcnew System::Windows::Forms::ListBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->txtModificarCurso = (gcnew System::Windows::Forms::TextBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->nudModificarInicio = (gcnew System::Windows::Forms::NumericUpDown());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->txtModificarDPI = (gcnew System::Windows::Forms::TextBox());
			this->txtModificarApellidos = (gcnew System::Windows::Forms::TextBox());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->txtModificarNombres = (gcnew System::Windows::Forms::TextBox());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
			this->btnBorrar = (gcnew System::Windows::Forms::Button());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->lbxBorrarDocentes = (gcnew System::Windows::Forms::ListBox());
			this->tabPage5 = (gcnew System::Windows::Forms::TabPage());
			this->lblSalarioPromedio = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->ofdOpen = (gcnew System::Windows::Forms::OpenFileDialog());
			this->tabControl1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvDatosDocentes))->BeginInit();
			this->tabPage1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudCrearSalario))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nupCrearInicio))->BeginInit();
			this->tabPage3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudModificarSalario))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudModificarInicio))->BeginInit();
			this->tabPage4->SuspendLayout();
			this->tabPage5->SuspendLayout();
			this->SuspendLayout();
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Controls->Add(this->tabPage4);
			this->tabControl1->Controls->Add(this->tabPage5);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Margin = System::Windows::Forms::Padding(4);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(445, 650);
			this->tabControl1->TabIndex = 1;
			// 
			// tabPage2
			// 
			this->tabPage2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tabPage2.BackgroundImage")));
			this->tabPage2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->tabPage2->Controls->Add(this->btnAbrir);
			this->tabPage2->Controls->Add(this->dgvDatosDocentes);
			this->tabPage2->Controls->Add(this->btnDatosGuardar);
			this->tabPage2->Controls->Add(this->label10);
			this->tabPage2->Location = System::Drawing::Point(4, 28);
			this->tabPage2->Margin = System::Windows::Forms::Padding(4);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(4);
			this->tabPage2->Size = System::Drawing::Size(437, 618);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Datos";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// btnAbrir
			// 
			this->btnAbrir->Location = System::Drawing::Point(18, 550);
			this->btnAbrir->Name = L"btnAbrir";
			this->btnAbrir->Size = System::Drawing::Size(198, 46);
			this->btnAbrir->TabIndex = 26;
			this->btnAbrir->Text = L"Abrir";
			this->btnAbrir->UseVisualStyleBackColor = true;
			this->btnAbrir->Click += gcnew System::EventHandler(this, &frmDocente::btnAbrir_Click);
			// 
			// dgvDatosDocentes
			// 
			this->dgvDatosDocentes->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvDatosDocentes->Location = System::Drawing::Point(18, 42);
			this->dgvDatosDocentes->Name = L"dgvDatosDocentes";
			this->dgvDatosDocentes->ReadOnly = true;
			this->dgvDatosDocentes->RowHeadersVisible = false;
			this->dgvDatosDocentes->RowHeadersWidth = 51;
			this->dgvDatosDocentes->RowTemplate->Height = 24;
			this->dgvDatosDocentes->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->dgvDatosDocentes->Size = System::Drawing::Size(400, 505);
			this->dgvDatosDocentes->TabIndex = 23;
			// 
			// btnDatosGuardar
			// 
			this->btnDatosGuardar->Location = System::Drawing::Point(235, 553);
			this->btnDatosGuardar->Name = L"btnDatosGuardar";
			this->btnDatosGuardar->Size = System::Drawing::Size(183, 40);
			this->btnDatosGuardar->TabIndex = 22;
			this->btnDatosGuardar->Text = L"Exportar";
			this->btnDatosGuardar->UseVisualStyleBackColor = true;
			this->btnDatosGuardar->Click += gcnew System::EventHandler(this, &frmDocente::btnDatosGuardar_Click);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(14, 16);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(80, 19);
			this->label10->TabIndex = 20;
			this->label10->Text = L"Docentes";
			// 
			// tabPage1
			// 
			this->tabPage1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tabPage1.BackgroundImage")));
			this->tabPage1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->tabPage1->Controls->Add(this->nudCrearSalario);
			this->tabPage1->Controls->Add(this->label5);
			this->tabPage1->Controls->Add(this->btnCrearEliminarCurso);
			this->tabPage1->Controls->Add(this->btnCrearRegistrar);
			this->tabPage1->Controls->Add(this->btnCrearAgregarCurso);
			this->tabPage1->Controls->Add(this->lbxCrearCursos);
			this->tabPage1->Controls->Add(this->label8);
			this->tabPage1->Controls->Add(this->txtCrearCurso);
			this->tabPage1->Controls->Add(this->label7);
			this->tabPage1->Controls->Add(this->nupCrearInicio);
			this->tabPage1->Controls->Add(this->label4);
			this->tabPage1->Controls->Add(this->txtCrearDPI);
			this->tabPage1->Controls->Add(this->txtCrearApellidos);
			this->tabPage1->Controls->Add(this->label3);
			this->tabPage1->Controls->Add(this->label2);
			this->tabPage1->Controls->Add(this->txtCrearNombres);
			this->tabPage1->Controls->Add(this->label1);
			this->tabPage1->Location = System::Drawing::Point(4, 28);
			this->tabPage1->Margin = System::Windows::Forms::Padding(4);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(4);
			this->tabPage1->Size = System::Drawing::Size(437, 618);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Crear";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// nudCrearSalario
			// 
			this->nudCrearSalario->DecimalPlaces = 2;
			this->nudCrearSalario->Location = System::Drawing::Point(136, 211);
			this->nudCrearSalario->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5000, 0, 0, 0 });
			this->nudCrearSalario->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->nudCrearSalario->Name = L"nudCrearSalario";
			this->nudCrearSalario->Size = System::Drawing::Size(293, 27);
			this->nudCrearSalario->TabIndex = 23;
			this->nudCrearSalario->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1500, 0, 0, 0 });
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->BackColor = System::Drawing::Color::LightSteelBlue;
			this->label5->Location = System::Drawing::Point(8, 213);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(66, 19);
			this->label5->TabIndex = 22;
			this->label5->Text = L"Salario:";
			// 
			// btnCrearEliminarCurso
			// 
			this->btnCrearEliminarCurso->BackColor = System::Drawing::Color::LightSteelBlue;
			this->btnCrearEliminarCurso->Location = System::Drawing::Point(278, 507);
			this->btnCrearEliminarCurso->Name = L"btnCrearEliminarCurso";
			this->btnCrearEliminarCurso->Size = System::Drawing::Size(151, 32);
			this->btnCrearEliminarCurso->TabIndex = 21;
			this->btnCrearEliminarCurso->Text = L"Eliminar";
			this->btnCrearEliminarCurso->UseVisualStyleBackColor = false;
			this->btnCrearEliminarCurso->Click += gcnew System::EventHandler(this, &frmDocente::btnCrearEliminarCurso_Click);
			// 
			// btnCrearRegistrar
			// 
			this->btnCrearRegistrar->BackColor = System::Drawing::Color::LightSteelBlue;
			this->btnCrearRegistrar->Location = System::Drawing::Point(65, 564);
			this->btnCrearRegistrar->Name = L"btnCrearRegistrar";
			this->btnCrearRegistrar->Size = System::Drawing::Size(298, 32);
			this->btnCrearRegistrar->TabIndex = 20;
			this->btnCrearRegistrar->Text = L"Registrar";
			this->btnCrearRegistrar->UseVisualStyleBackColor = false;
			this->btnCrearRegistrar->Click += gcnew System::EventHandler(this, &frmDocente::btnCrearRegistrar_Click);
			// 
			// btnCrearAgregarCurso
			// 
			this->btnCrearAgregarCurso->BackColor = System::Drawing::Color::LightSteelBlue;
			this->btnCrearAgregarCurso->Location = System::Drawing::Point(278, 321);
			this->btnCrearAgregarCurso->Name = L"btnCrearAgregarCurso";
			this->btnCrearAgregarCurso->Size = System::Drawing::Size(151, 32);
			this->btnCrearAgregarCurso->TabIndex = 19;
			this->btnCrearAgregarCurso->Text = L"Agregar";
			this->btnCrearAgregarCurso->UseVisualStyleBackColor = false;
			this->btnCrearAgregarCurso->Click += gcnew System::EventHandler(this, &frmDocente::btnCrearAgregarCurso_Click);
			// 
			// lbxCrearCursos
			// 
			this->lbxCrearCursos->FormattingEnabled = true;
			this->lbxCrearCursos->ItemHeight = 19;
			this->lbxCrearCursos->Location = System::Drawing::Point(12, 359);
			this->lbxCrearCursos->Name = L"lbxCrearCursos";
			this->lbxCrearCursos->Size = System::Drawing::Size(417, 80);
			this->lbxCrearCursos->TabIndex = 18;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->BackColor = System::Drawing::Color::LightSteelBlue;
			this->label8->Location = System::Drawing::Point(8, 324);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(77, 19);
			this->label8->TabIndex = 16;
			this->label8->Text = L"Nombre:";
			// 
			// txtCrearCurso
			// 
			this->txtCrearCurso->Location = System::Drawing::Point(136, 321);
			this->txtCrearCurso->Name = L"txtCrearCurso";
			this->txtCrearCurso->Size = System::Drawing::Size(132, 27);
			this->txtCrearCurso->TabIndex = 14;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->BackColor = System::Drawing::Color::LightSteelBlue;
			this->label7->Location = System::Drawing::Point(8, 280);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(62, 19);
			this->label7->TabIndex = 13;
			this->label7->Text = L"Cursos:";
			// 
			// nupCrearInicio
			// 
			this->nupCrearInicio->Location = System::Drawing::Point(136, 173);
			this->nupCrearInicio->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 20451231, 0, 0, 0 });
			this->nupCrearInicio->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 19800101, 0, 0, 0 });
			this->nupCrearInicio->Name = L"nupCrearInicio";
			this->nupCrearInicio->Size = System::Drawing::Size(293, 27);
			this->nupCrearInicio->TabIndex = 12;
			this->nupCrearInicio->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 19800101, 0, 0, 0 });
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::LightSteelBlue;
			this->label4->Location = System::Drawing::Point(8, 175);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(55, 19);
			this->label4->TabIndex = 6;
			this->label4->Text = L"Inicio:";
			// 
			// txtCrearDPI
			// 
			this->txtCrearDPI->Location = System::Drawing::Point(136, 92);
			this->txtCrearDPI->Name = L"txtCrearDPI";
			this->txtCrearDPI->Size = System::Drawing::Size(293, 27);
			this->txtCrearDPI->TabIndex = 5;
			// 
			// txtCrearApellidos
			// 
			this->txtCrearApellidos->Location = System::Drawing::Point(136, 54);
			this->txtCrearApellidos->Name = L"txtCrearApellidos";
			this->txtCrearApellidos->Size = System::Drawing::Size(293, 27);
			this->txtCrearApellidos->TabIndex = 4;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::LightSteelBlue;
			this->label3->Location = System::Drawing::Point(8, 95);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(37, 19);
			this->label3->TabIndex = 3;
			this->label3->Text = L"DPI:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::LightSteelBlue;
			this->label2->Location = System::Drawing::Point(8, 57);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(85, 19);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Apellidos:";
			// 
			// txtCrearNombres
			// 
			this->txtCrearNombres->Location = System::Drawing::Point(136, 16);
			this->txtCrearNombres->Name = L"txtCrearNombres";
			this->txtCrearNombres->Size = System::Drawing::Size(293, 27);
			this->txtCrearNombres->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::LightSteelBlue;
			this->label1->Location = System::Drawing::Point(8, 19);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(83, 19);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Nombres:";
			// 
			// tabPage3
			// 
			this->tabPage3->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tabPage3.BackgroundImage")));
			this->tabPage3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->tabPage3->Controls->Add(this->btnModificarAgregarCurso);
			this->tabPage3->Controls->Add(this->nudModificarSalario);
			this->tabPage3->Controls->Add(this->label6);
			this->tabPage3->Controls->Add(this->label21);
			this->tabPage3->Controls->Add(this->cbxModificarDocentes);
			this->tabPage3->Controls->Add(this->btnModificarEliminarCurso);
			this->tabPage3->Controls->Add(this->btnModificar);
			this->tabPage3->Controls->Add(this->lbxModificarCursos);
			this->tabPage3->Controls->Add(this->label13);
			this->tabPage3->Controls->Add(this->txtModificarCurso);
			this->tabPage3->Controls->Add(this->label14);
			this->tabPage3->Controls->Add(this->nudModificarInicio);
			this->tabPage3->Controls->Add(this->label17);
			this->tabPage3->Controls->Add(this->txtModificarDPI);
			this->tabPage3->Controls->Add(this->txtModificarApellidos);
			this->tabPage3->Controls->Add(this->label18);
			this->tabPage3->Controls->Add(this->label19);
			this->tabPage3->Controls->Add(this->txtModificarNombres);
			this->tabPage3->Controls->Add(this->label20);
			this->tabPage3->Location = System::Drawing::Point(4, 28);
			this->tabPage3->Margin = System::Windows::Forms::Padding(4);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(4);
			this->tabPage3->Size = System::Drawing::Size(437, 618);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Modificar";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// btnModificarAgregarCurso
			// 
			this->btnModificarAgregarCurso->Location = System::Drawing::Point(278, 316);
			this->btnModificarAgregarCurso->Name = L"btnModificarAgregarCurso";
			this->btnModificarAgregarCurso->Size = System::Drawing::Size(151, 32);
			this->btnModificarAgregarCurso->TabIndex = 47;
			this->btnModificarAgregarCurso->Text = L"Agregar";
			this->btnModificarAgregarCurso->UseVisualStyleBackColor = true;
			this->btnModificarAgregarCurso->Click += gcnew System::EventHandler(this, &frmDocente::btnModificarAgregarCurso_Click);
			// 
			// nudModificarSalario
			// 
			this->nudModificarSalario->DecimalPlaces = 2;
			this->nudModificarSalario->Location = System::Drawing::Point(136, 225);
			this->nudModificarSalario->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
			this->nudModificarSalario->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->nudModificarSalario->Name = L"nudModificarSalario";
			this->nudModificarSalario->Size = System::Drawing::Size(293, 27);
			this->nudModificarSalario->TabIndex = 46;
			this->nudModificarSalario->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1500, 0, 0, 0 });
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->BackColor = System::Drawing::Color::LightSteelBlue;
			this->label6->Location = System::Drawing::Point(8, 227);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(66, 19);
			this->label6->TabIndex = 45;
			this->label6->Text = L"Salario:";
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->BackColor = System::Drawing::Color::LightSteelBlue;
			this->label21->Location = System::Drawing::Point(8, 12);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(84, 19);
			this->label21->TabIndex = 44;
			this->label21->Text = L"Docentes:";
			// 
			// cbxModificarDocentes
			// 
			this->cbxModificarDocentes->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbxModificarDocentes->FormattingEnabled = true;
			this->cbxModificarDocentes->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Doctorado", L"Pregrado", L"Postgrado" });
			this->cbxModificarDocentes->Location = System::Drawing::Point(136, 9);
			this->cbxModificarDocentes->Name = L"cbxModificarDocentes";
			this->cbxModificarDocentes->Size = System::Drawing::Size(293, 27);
			this->cbxModificarDocentes->TabIndex = 43;
			this->cbxModificarDocentes->SelectedIndexChanged += gcnew System::EventHandler(this, &frmDocente::cbxModificarDocentes_SelectedIndexChanged);
			// 
			// btnModificarEliminarCurso
			// 
			this->btnModificarEliminarCurso->Location = System::Drawing::Point(278, 523);
			this->btnModificarEliminarCurso->Name = L"btnModificarEliminarCurso";
			this->btnModificarEliminarCurso->Size = System::Drawing::Size(151, 32);
			this->btnModificarEliminarCurso->TabIndex = 42;
			this->btnModificarEliminarCurso->Text = L"Eliminar";
			this->btnModificarEliminarCurso->UseVisualStyleBackColor = true;
			this->btnModificarEliminarCurso->Click += gcnew System::EventHandler(this, &frmDocente::btnModificarEliminarCurso_Click);
			// 
			// btnModificar
			// 
			this->btnModificar->Location = System::Drawing::Point(65, 565);
			this->btnModificar->Name = L"btnModificar";
			this->btnModificar->Size = System::Drawing::Size(298, 32);
			this->btnModificar->TabIndex = 41;
			this->btnModificar->Text = L"Modificar";
			this->btnModificar->UseVisualStyleBackColor = true;
			this->btnModificar->Click += gcnew System::EventHandler(this, &frmDocente::btnModificar_Click);
			// 
			// lbxModificarCursos
			// 
			this->lbxModificarCursos->FormattingEnabled = true;
			this->lbxModificarCursos->ItemHeight = 19;
			this->lbxModificarCursos->Location = System::Drawing::Point(13, 375);
			this->lbxModificarCursos->Name = L"lbxModificarCursos";
			this->lbxModificarCursos->Size = System::Drawing::Size(417, 80);
			this->lbxModificarCursos->TabIndex = 39;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->BackColor = System::Drawing::Color::LightSteelBlue;
			this->label13->Location = System::Drawing::Point(8, 319);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(77, 19);
			this->label13->TabIndex = 37;
			this->label13->Text = L"Nombre:";
			// 
			// txtModificarCurso
			// 
			this->txtModificarCurso->Location = System::Drawing::Point(136, 316);
			this->txtModificarCurso->Name = L"txtModificarCurso";
			this->txtModificarCurso->Size = System::Drawing::Size(136, 27);
			this->txtModificarCurso->TabIndex = 35;
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->BackColor = System::Drawing::Color::LightSteelBlue;
			this->label14->Location = System::Drawing::Point(8, 284);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(62, 19);
			this->label14->TabIndex = 34;
			this->label14->Text = L"Cursos:";
			// 
			// nudModificarInicio
			// 
			this->nudModificarInicio->Location = System::Drawing::Point(136, 187);
			this->nudModificarInicio->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 20451231, 0, 0, 0 });
			this->nudModificarInicio->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 19800101, 0, 0, 0 });
			this->nudModificarInicio->Name = L"nudModificarInicio";
			this->nudModificarInicio->Size = System::Drawing::Size(293, 27);
			this->nudModificarInicio->TabIndex = 33;
			this->nudModificarInicio->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 19800101, 0, 0, 0 });
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->BackColor = System::Drawing::Color::LightSteelBlue;
			this->label17->Location = System::Drawing::Point(8, 189);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(55, 19);
			this->label17->TabIndex = 28;
			this->label17->Text = L"Inicio:";
			// 
			// txtModificarDPI
			// 
			this->txtModificarDPI->Location = System::Drawing::Point(136, 134);
			this->txtModificarDPI->Name = L"txtModificarDPI";
			this->txtModificarDPI->Size = System::Drawing::Size(293, 27);
			this->txtModificarDPI->TabIndex = 27;
			// 
			// txtModificarApellidos
			// 
			this->txtModificarApellidos->Location = System::Drawing::Point(136, 96);
			this->txtModificarApellidos->Name = L"txtModificarApellidos";
			this->txtModificarApellidos->Size = System::Drawing::Size(293, 27);
			this->txtModificarApellidos->TabIndex = 26;
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->BackColor = System::Drawing::Color::LightSteelBlue;
			this->label18->Location = System::Drawing::Point(8, 137);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(37, 19);
			this->label18->TabIndex = 25;
			this->label18->Text = L"DPI:";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->BackColor = System::Drawing::Color::LightSteelBlue;
			this->label19->Location = System::Drawing::Point(8, 99);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(85, 19);
			this->label19->TabIndex = 24;
			this->label19->Text = L"Apellidos:";
			// 
			// txtModificarNombres
			// 
			this->txtModificarNombres->Location = System::Drawing::Point(136, 58);
			this->txtModificarNombres->Name = L"txtModificarNombres";
			this->txtModificarNombres->Size = System::Drawing::Size(293, 27);
			this->txtModificarNombres->TabIndex = 23;
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->BackColor = System::Drawing::Color::LightSteelBlue;
			this->label20->Location = System::Drawing::Point(8, 61);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(83, 19);
			this->label20->TabIndex = 22;
			this->label20->Text = L"Nombres:";
			// 
			// tabPage4
			// 
			this->tabPage4->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tabPage4.BackgroundImage")));
			this->tabPage4->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->tabPage4->Controls->Add(this->btnBorrar);
			this->tabPage4->Controls->Add(this->label11);
			this->tabPage4->Controls->Add(this->lbxBorrarDocentes);
			this->tabPage4->Location = System::Drawing::Point(4, 28);
			this->tabPage4->Margin = System::Windows::Forms::Padding(4);
			this->tabPage4->Name = L"tabPage4";
			this->tabPage4->Padding = System::Windows::Forms::Padding(4);
			this->tabPage4->Size = System::Drawing::Size(437, 618);
			this->tabPage4->TabIndex = 3;
			this->tabPage4->Text = L"Borrar";
			this->tabPage4->UseVisualStyleBackColor = true;
			// 
			// btnBorrar
			// 
			this->btnBorrar->Location = System::Drawing::Point(127, 551);
			this->btnBorrar->Name = L"btnBorrar";
			this->btnBorrar->Size = System::Drawing::Size(183, 40);
			this->btnBorrar->TabIndex = 24;
			this->btnBorrar->Text = L"Borrar";
			this->btnBorrar->UseVisualStyleBackColor = true;
			this->btnBorrar->Click += gcnew System::EventHandler(this, &frmDocente::btnBorrar_Click);
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(13, 19);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(80, 19);
			this->label11->TabIndex = 23;
			this->label11->Text = L"Docentes";
			// 
			// lbxBorrarDocentes
			// 
			this->lbxBorrarDocentes->FormattingEnabled = true;
			this->lbxBorrarDocentes->ItemHeight = 19;
			this->lbxBorrarDocentes->Location = System::Drawing::Point(13, 45);
			this->lbxBorrarDocentes->Name = L"lbxBorrarDocentes";
			this->lbxBorrarDocentes->Size = System::Drawing::Size(410, 441);
			this->lbxBorrarDocentes->TabIndex = 22;
			// 
			// tabPage5
			// 
			this->tabPage5->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tabPage5.BackgroundImage")));
			this->tabPage5->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->tabPage5->Controls->Add(this->lblSalarioPromedio);
			this->tabPage5->Controls->Add(this->label9);
			this->tabPage5->Location = System::Drawing::Point(4, 28);
			this->tabPage5->Name = L"tabPage5";
			this->tabPage5->Padding = System::Windows::Forms::Padding(3);
			this->tabPage5->Size = System::Drawing::Size(437, 618);
			this->tabPage5->TabIndex = 4;
			this->tabPage5->Text = L"Reportes";
			this->tabPage5->UseVisualStyleBackColor = true;
			// 
			// lblSalarioPromedio
			// 
			this->lblSalarioPromedio->AutoSize = true;
			this->lblSalarioPromedio->BackColor = System::Drawing::Color::LightSteelBlue;
			this->lblSalarioPromedio->Location = System::Drawing::Point(282, 134);
			this->lblSalarioPromedio->Name = L"lblSalarioPromedio";
			this->lblSalarioPromedio->Size = System::Drawing::Size(40, 19);
			this->lblSalarioPromedio->TabIndex = 1;
			this->lblSalarioPromedio->Text = L"0.00";
			this->lblSalarioPromedio->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->BackColor = System::Drawing::Color::LightSteelBlue;
			this->label9->Location = System::Drawing::Point(94, 134);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(147, 19);
			this->label9->TabIndex = 0;
			this->label9->Text = L"Salario promedio:";
			// 
			// ofdOpen
			// 
			this->ofdOpen->Filter = L"CSV File|*.csv";
			this->ofdOpen->Title = L"Abrir Archivo";
			// 
			// frmDocente
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 19);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(445, 650);
			this->Controls->Add(this->tabControl1);
			this->Font = (gcnew System::Drawing::Font(L"Century Gothic", 12, System::Drawing::FontStyle::Bold));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"frmDocente";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"frmDocente";
			this->Load += gcnew System::EventHandler(this, &frmDocente::frmDocente_Load);
			this->tabControl1->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvDatosDocentes))->EndInit();
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudCrearSalario))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nupCrearInicio))->EndInit();
			this->tabPage3->ResumeLayout(false);
			this->tabPage3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudModificarSalario))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudModificarInicio))->EndInit();
			this->tabPage4->ResumeLayout(false);
			this->tabPage4->PerformLayout();
			this->tabPage5->ResumeLayout(false);
			this->tabPage5->PerformLayout();
			this->ResumeLayout(false);

		}
	#pragma endregion
	private: System::Void frmDocente_Load(System::Object^ sender, System::EventArgs^ e)
	{

	}
	private: System::Void btnCrearRegistrar_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		if (txtCrearDPI->Text->Length != 15)
		{
			MessageBox::Show("DPI inválido");
			return;
		}

		Docente* docente = new Docente();
		docente->Nombres = StdString(txtCrearNombres->Text);
		docente->Apellidos = StdString(txtCrearApellidos->Text);
		docente->DPI = StdString(txtCrearDPI->Text);

		docente->Inicio = (int)nupCrearInicio->Value;
		docente->Salario = (float)nudCrearSalario->Value;

		docente->Cursos = cursos;
		docente->Codigo = (rand() % (100000 - 10000) + 10000) * 100 + ((docente->Inicio / 10000) % 100);
		docentes->Insertar(docente);

		txtCrearNombres->Clear();
		txtCrearApellidos->Clear();
		txtCrearDPI->Clear();
		nupCrearInicio->Value = 19800101;
		nudCrearSalario->Value = 1500;
		cursos = new Lista<Curso*>;

		LlenarDatosDocentes();
	}
private: System::Void btnCrearAgregarCurso_Click(System::Object^ sender, System::EventArgs^ e)
{
	Curso* curso = new Curso();
	curso->Nombre = StdString(txtCrearCurso->Text);

	txtCrearCurso->Clear();

	cursos->Insertar(curso);
	LlenarDatosDocentes();
}
private: System::Void btnCrearEliminarCurso_Click(System::Object^ sender, System::EventArgs^ e) 
{
	if (lbxCrearCursos->SelectedIndex != -1)
	{
		cursos->Extraer(lbxCrearCursos->SelectedIndex);
		LlenarDatosDocentes();
	}
}
private: System::Void btnModificar_Click(System::Object^ sender, System::EventArgs^ e) 
{
	if (docenteModificar != nullptr)
	{
		if (txtModificarDPI->Text->Length != 15)
		{
			MessageBox::Show("DPI inválido");
			return;
		}
		docenteModificar->Nombres = StdString(txtModificarNombres->Text);
		docenteModificar->Apellidos = StdString(txtModificarApellidos->Text);
		docenteModificar->DPI = StdString(txtModificarDPI->Text);

		docenteModificar->Inicio = (int)nudModificarInicio->Value;
		docenteModificar->Salario = (float)nudModificarSalario->Value;
		docenteModificar->Codigo = (rand() % (100000 - 10000) + 10000) * 100 + ((docenteModificar->Inicio / 10000) % 100);
	
		LlenarDatosDocentes();
	}
}
private: System::Void btnModificarAgregarCurso_Click(System::Object^ sender, System::EventArgs^ e) 
{
	if (docenteModificar != nullptr)
	{
		Curso* curso = new Curso();
		curso->Nombre = StdString(txtModificarCurso->Text);

		txtModificarCurso->Clear();

		docenteModificar->Cursos->Insertar(curso);
		LlenarDatosDocentes();
	}
}
private: System::Void btnModificarEliminarCurso_Click(System::Object^ sender, System::EventArgs^ e) 
{
	if (docenteModificar != nullptr)
	{
		if (lbxModificarCursos->SelectedIndex != -1)
		{
			docenteModificar->Cursos->Extraer(lbxModificarCursos->SelectedIndex);
			LlenarDatosDocentes();
		}
	}
}
private: System::Void cbxModificarDocentes_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) 
{
	if (cbxModificarDocentes->SelectedIndex != -1)
	{
		Docente* docente = docentes->Obtener(cbxModificarDocentes->SelectedIndex);
		txtModificarNombres->Text = VisualString(docente->Nombres);
		txtModificarApellidos->Text = VisualString(docente->Apellidos);
		txtModificarDPI->Text = VisualString(docente->DPI);

		nudModificarInicio->Value = docente->Inicio;
		nudModificarSalario->Value = Convert::ToDecimal( docente->Salario );

		docenteModificar = docente;
		LlenarDatosDocentes();
	}
	else
	{
		txtModificarNombres->Clear();
		txtModificarApellidos->Clear();
		txtModificarDPI->Clear();

		nudModificarInicio->Value = 0;
		nudModificarSalario->Value = 1500;

		docenteModificar = nullptr;
	}
}
private: System::Void btnBorrar_Click(System::Object^ sender, System::EventArgs^ e) 
{
	if (lbxBorrarDocentes->SelectedIndex != -1)
	{
		docentes->Extraer(lbxBorrarDocentes->SelectedIndex);
		LlenarDatosDocentes();
	}
}
private: System::Void btnDatosGuardar_Click(System::Object^ sender, System::EventArgs^ e)
{
	for (int i = 0; i < docentes->cantidad - 1; i++)
		for (int j = i + 1; j < docentes->cantidad; j++)
		{
			Docente* docente1 = docentes->Obtener(i);
			Docente* docente2 = docentes->Obtener(j);
			if (docente1->Apellidos > docente2->Apellidos)
			{
				docentes->Intercambiar(i, j);
			}
		}


	CsvWriter* csv = new CsvWriter();
	for (int i = 0; i < docentes->cantidad; i++)
	{
		Docente* docente = docentes->Obtener(i);
		csv->Write(StdString(docente->Codigo.ToString()));
		csv->Write(docente->Apellidos);
		csv->Write(docente->Nombres);
		csv->Write(docente->DPI);
		csv->Write(StdString(docente->Inicio.ToString()));
		csv->Write(StdString(docente->Salario.ToString()));
		for (int j = 0; j < docente->Cursos->cantidad; j++)
		{
			Curso* curso = docente->Cursos->Obtener(j);
			csv->Write(curso->Nombre);
		}
		csv->NextLine();
	}
	csv->Save("data/exportardocentes-data.csv");
	MessageBox::Show("OPERACION REALIZADA EXITOSAMENTE", "OPERACION EXPORTAR", MessageBoxButtons::OK, MessageBoxIcon::Information);
}
private: System::Void btnAbrir_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (ofdOpen->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		LeerCSV(ofdOpen->FileName);
		LlenarDatosDocentes();
	}
}
};
}
