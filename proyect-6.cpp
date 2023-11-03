// bibliotecas necesarias para el uso del programa
#include <algorithm> // funciones de algoritmo como sort(), find().
#include <cstdlib>   // funciones generales como malloc(), free(), exit() .
#include <iostream>  // funciones para entrada/salida
#include <limits>    // información sobre los límites de los tipos de datos
#include <map>       // tipo de datos map (diccionario)
#include <random>    // funciones para generar números aleatorios
#include <string>    // tipo de datos string y funciones asociadas
#include <vector>    // tipo de datos vector (array dinámico)

// Permite el uso de los nombres de la biblioteca estándar directamente, sin
// necesidad de anteponer 'std::'
using namespace std;

struct Servicio {
  string nombre;
  string descripcion;
};
struct Plan {
  string nombre;
  string descripcion;
  vector<Servicio> serviciosIncluidos;
  string tipoPlan;
  int precio;
};

// tipos que puede tener un plan
vector<string> tiposPlan = {"residencial", "movil"};

struct Mantenimientos {
  int id;
  string nombreDelServicio;
  string status;
};

struct Quejas {
  string id;
  string status;
  string description;
};

struct Usuario {
  string nombre;
  string apellido;
  string DPI;
  string direccion;
  string NIT;
  string contacto;
  string contrasena;
  string tipoCliente;
  Plan planServicio;
  vector<Mantenimientos> mantenimientos;
  vector<Quejas> quejas;
};

map<string, Usuario> usuarios;
vector<Servicio> servicios;
vector<Plan> planes;
Usuario usuarioActual = {};
Usuario registrarUsuario();
void menuUsuario(string &contactoActual);
string contactoActual = "";
void verEstadoMantenimientos();
void verEstadoQuejas();

// funciones utiles
// encontrar index de un servicio particular
int encontrarIndiceDePlan(vector<Plan> plans, string elementoBuscado) {
  for (int i = 0; i < plans.size(); i++) {
    if (plans[i].nombre == elementoBuscado) {
      return i; // Devuelve el índice si se encuentra el elemento.
    }
  }
  return -1; // Devuelve -1 si el elemento no se encuentra.
}

void irAMenuUsuario() {
  cin.clear();
  cout << "------------------------------------\n";
  cout << "Oprime Cualquier tecla para continuar...\n";
  cout << "------------------------------------\n";
  cin.get(); // Esperamos a que el usuario presione Enter
  menuUsuario(contactoActual);
}

// creacion de un id random
string generarID(int longitud) {
  const string caracteres =
      "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  random_device rd;
  std::mt19937 generador(rd());
  std::uniform_int_distribution<int> distribucion(0, caracteres.size() - 1);

  string idGenerado = "";
  for (int i = 0; i < longitud; i++) {
    int indice = distribucion(generador);
    idGenerado += caracteres[indice];
  }
  return idGenerado;
}

void inicializarServiciosYPlanes() {
  // Definici�n de servicios
  servicios.push_back({"Internet", "Conexion a Internet de 50 Mbps"});
  servicios.push_back({"Internet", "Conexion a Internet de 100 Mbps"});
  servicios.push_back({"Telefono", "Linea telefonica con llamadas ilimitadas"});
  servicios.push_back({"Internet premium", "Conexion a Internet de 200 Mbps"});
  servicios.push_back({"Telefono", "100 minutos de llamadas telefonicas"});
  servicios.push_back({"Telefono", "300 minutos de llamadas telefonicas"});
  servicios.push_back({"Telefono", "Sms ilimitados"});
  servicios.push_back({"Internet", "2GB datos"});
  servicios.push_back({"Internet", "5GB datos"});
  servicios.push_back({"Internet", "10GB datos"});
  servicios.push_back({"TV", "100 Canales"});
  servicios.push_back({"TV", "200 Canales"});
  servicios.push_back({"TV", "Canales de Deportes"});
  cout << "servicios iniciados\n";
  cout << "tipos de servicios actuales" << tiposPlan[0] << " " << tiposPlan[1] << "\n";
  // Definici�n de planes
  Plan planResidencialTelefono = {"Plan Residencial Telefono",
                                  "Plan Residencial basico con Telefono",
                                  {servicios[2]},
                                  tiposPlan[0],
                                  700};
  Plan planResidencialTelefonoTV = {
      "Plan Residencial Telefono + TV",
      "Plan Residencial basico con Telefono + Television",
      {servicios[2], servicios[11]},
      tiposPlan[0],
      900};
  Plan planResidencialBasico = {
      "Plan Residencial Basico",
      "Plan Residencial basico con Internet y Telefono",
      {servicios[0], servicios[2]},
      tiposPlan[0],
      1200};
  Plan planResidencialTriple = {
      "Plan Residencial Triple Telefono + TV + Internet",
      "Plan Residencial basico con Telefono + Television +  Internet",
      {servicios[2], servicios[11], servicios[0]},
      tiposPlan[0],
      1250};
  Plan planResidencialPremium = {"Plan Residencial Premium",
                                 "Plan Residencial Premium con Internet ultra "
                                 "rapido, llamadas internacionales y TV"
                                 "ilimitadas",
                                 {servicios[1], servicios[2], servicios[10]},
                                 tiposPlan[0],
                                 1400};
  Plan planResidencialSuperPremium = {
      "Plan Residencial Super Premium",
      "Plan Residencial Super Premium con el Internet mas rapido rapido, "
      "llamadas internacionales y todos los canales de tv que puedes desear"
      "ilimitadas",
      {servicios[1], servicios[2], servicios[11], servicios[12]},
      tiposPlan[0],
      1800};
  Plan planMovilBasico = {"Plan Movil basico",
                          "Plan movil con minutos e internet",
                          {servicios[4], servicios[7]},
                          tiposPlan[1],
                          400};
  Plan planMovilMejorado = {"Plan Movil Mejorado",
                            "Plan movil con mas minutos e internet",
                            {servicios[5], servicios[8]},
                            tiposPlan[1],
                            600};
  Plan planMovilMaximo = {
      "Plan Movil Maximo",
      "Plan movil con minutos, sms ilimitados y mucho mas internet",
      {servicios[2], servicios[9], servicios[6]},
      tiposPlan[1],
      750};
  planes.push_back(planResidencialTelefono);
  planes.push_back(planResidencialTelefonoTV);
  planes.push_back(planResidencialBasico);
  planes.push_back(planResidencialTriple);
  planes.push_back(planResidencialPremium);
  planes.push_back(planResidencialSuperPremium);
  planes.push_back(planMovilBasico);
  planes.push_back(planMovilMejorado);
  planes.push_back(planMovilMaximo);
  cout << "planes iniciados";
return;
}

void inicializarUsuarios() {
  Usuario usuario1 = {"Juan",       "Perez",   "1234567890123",
                      "Calle 1",    "1234567", "contacto1",
                       "pass1", "Particular",   planes[0]};
  Usuario usuario2 = {"Maria",   "Gonzalez",  "9876543210987", "Calle 2",
                      "7654321", "contacto2","pass2", "Empresarial"};
  usuarios["contacto1"] = usuario1;
  usuarios["contacto2"] = usuario2;
  return;
}

Usuario UsuarioTemporal() {
  Usuario usuarioTemporal = {"User",       "Temp",   "0000000",
                             "Calle 0",    "000000", "contact0 0",
                             "Particular", "pass0",  {}};
  return usuarioTemporal;
}

void mejorarPlan(Usuario &usuario){
	 const int planActual = encontrarIndiceDePlan(planes, usuario.planServicio.nombre);
    if (planActual != -1 && planActual < planes.size()) {
      if(planes[planActual].nombre == "Plan Residencial Super Premium" || planes[planActual].nombre == "Plan Movil Maximo"){
      	 cout << "-----------------------------------------------\n";
      	 cout << "Ya Cuentas con el mejor plan posible\n";
      	 cout << "-----------------------------------------------\n";
      	irAMenuUsuario();
	  }
      int mejorplan = planActual + 1;
      cout << "-----------------------------------------------\n";
      cout << "Puedes mejorar al plan: " << planes[mejorplan].nombre << endl;
      for (const auto &servicio : planes[mejorplan].serviciosIncluidos) {
        cout << "- " << servicio.nombre << ": " << servicio.descripcion << endl;
      }
      int opcion;
      do {
        cout << "--------------------------------------------------------------"
                "\n";
        cout << "1. para mejorar al plan : " << planes[mejorplan].nombre
             << endl;
        cout << "2. para volver al menu principal " << endl;
        cout << "Elige una opcion: ";
        cin >> opcion;
        cin.ignore(std::numeric_limits<std::streamsize>::max(),
                   '\n'); // Limpia el buffer de entrada después de cada entrada
                          // del usuario
      } while (opcion != 1 && opcion != 2);

      if (opcion == 1) {

        usuario.planServicio = planes[mejorplan];
        cout << "Tu plan ha sido actualizado al plan : "
             << planes[mejorplan].nombre << endl;

        int opcionRegresar;
        do {
          cout << "------------------------------------------------------------"
                  "--\n";
          cout << "1. Regresar al menu principal" << endl;
          cin >> opcionRegresar;
          cin.ignore(std::numeric_limits<std::streamsize>::max(),
                     '\n'); // Limpia el buffer de entrada después de cada
                            // entrada del usuario
        } while (opcionRegresar != 1);

        if (opcionRegresar == 1) {
          irAMenuUsuario();
        }
      } else if (opcion == 2) {
        irAMenuUsuario();
      }
}
}
void mostrarDatosUsuario(Usuario &usuario) {

  cout << "-----------------------------------------------";
  cout << "\n INFORMACION DEL USUARIO " << endl;
  cout << "-----------------------------------------------\n";
  cout << "Nombre: " << usuario.nombre << endl;
  cout << "Apellido: " << usuario.apellido << endl;
  cout << "DPI: " << usuario.DPI << endl;
  cout << "Direccion: " << usuario.direccion << endl;
  cout << "NIT: " << usuario.NIT << endl;
  cout << "Contacto: " << usuario.contacto << endl;
  cout << "Tipo de Cliente: " << usuario.tipoCliente << endl;
  cout << "-----------------------------------------------\n\n";

  if (usuario.planServicio.nombre.empty()) {
    cout << "Actualmente no cuentas con ningun plan activo" << endl;
  } else {
    cout << "-----------------------------------------------\n";
    cout << "PLAN DE SERCVICIO ACTUAL: " << usuario.planServicio.nombre << endl;
    cout << "-----------------------------------------------\n";
    cout << "Servicios incluidos: " << endl;
    for (const auto &servicio : usuario.planServicio.serviciosIncluidos) {
      cout << "- " << servicio.nombre << ": " << servicio.descripcion << endl;
    }
    mejorarPlan(usuario);
    }
}

int mostrarServicios() {
  int opcion;
  do {

    int optionindex = 1;
    for (const auto &servicio : usuarioActual.planServicio.serviciosIncluidos) {
      cout << optionindex << ". " << servicio.nombre << ": "
           << servicio.descripcion << endl;
      optionindex++;
    }
    cout << "9. Volver\n";
    cout << "Elige una opcion: ";
    cin >> opcion;
    cin.ignore(); // Limpia el buffer
    if (opcion == 9) {
      return 0; // Retorna al menú anterior
    } else if (opcion > 0 &&
               opcion <= usuarioActual.planServicio.serviciosIncluidos.size()) {
      opcion = opcion - 1; // Restamos 1 a la opción para que coincida con el
                           // índice del vector
      cout << "Has elegido:"
           << usuarioActual.planServicio.serviciosIncluidos[opcion].nombre
           << endl;
      if (usuarioActual.mantenimientos.size() < 1) {
        usuarioActual.mantenimientos.push_back(
            {1, usuarioActual.planServicio.serviciosIncluidos[opcion].nombre,
             "pendiente"});
      } else {
        int index = usuarioActual.mantenimientos.size() - 1;
        usuarioActual.mantenimientos.push_back(
            {usuarioActual.mantenimientos[index].id + 1,
             usuarioActual.planServicio.serviciosIncluidos[opcion].nombre,
             "pendiente"});
      }
      cout << "El mantenimiento para el servicio "
           << usuarioActual.planServicio.serviciosIncluidos[opcion].nombre
           << " ha sido programado." << endl;
      cout << usuarioActual.mantenimientos.size() << endl;
      return 0;
    } else {
      cout << "Opcion invalida" << endl;
    }
  } while (opcion != 9);
  return 0;
};

int mostrarPlanes(int tipoPlan) {
  int opcion;
  vector<Plan> planesEspecificos = {};
  do {
    cout << "Escoge el plan que quieras comprar: \n";
    int index = 1;
    for (const auto &plan : planes) {
      if (plan.tipoPlan == tiposPlan[tipoPlan]) {
        cout << index << ". " << plan.nombre << " - " << plan.descripcion
             << endl;
        planesEspecificos.push_back(plan);
        index++;
      }
    }
    cout << "0. Volver al menu principal\n";
    cin >> opcion;
    cin.ignore(); // Limpia el buffer
  } while (opcion < 0 || opcion > planes.size());
  if (opcion != 0) {

    if (usuarioActual.nombre.empty()) {
      cout << "---------------------------------------\n";
      cout << "Debes crear una cuenta antes de poder escoger un plan:" << endl;
      cout << "---------------------------------------\n";
      usuarioActual = registrarUsuario();
    }
    int indexplan = opcion - 1;
    usuarioActual.planServicio = planesEspecificos[indexplan];
    cout << "---------------------------------------\n";
    cout << "El plan: " << usuarioActual.planServicio.nombre
         << " ha sido activado en tu cuenta!" << endl;
    cout << "---------------------------------------\n";
    irAMenuUsuario();
  }
  return 0;
}
void mostrarTipoPlanes() {
  int opcion;
  do {
    cout << "\n--- PLANES Y PAQUETES ---\n";
    cout << "--- Escoge que tipo de plan te interesa ---\n";
    cout << "1. Planes Residenciales\n";
    cout << "2. Planes Movil\n";
    cout << "0. Volver\n";
    cin >> opcion;
  } while (opcion < 0 || opcion > 2);
  if (opcion == 0) {
    return;
  } else {
    mostrarPlanes(opcion - 1);
  }
}
void escribirConsultaGeneral() {
  cout << "Escribe tu consulta a continuacion:\n";
  string consulta = "";
  cin.ignore();
  getline(cin, consulta);
  cout << "-----------------------------------------------"
          "--\n";
  cout << "Tu consulta se envio a uno de nuestros asesores pronto nos "
          "comunicaremos contigo.\n";
  cout << "-----------------------------------------------"
          "--\n";
  irAMenuUsuario();
}

void consultaPromociones() {
  cout << "Escribe tu consulta sobre promociones a continuacion:\n";
  string consulta = "";
  cin.ignore();
  getline(cin, consulta);
  cout << "-----------------------------------------------"
          "--\n";
  cout << "Tu consulta se envio a uno de nuestros asesores pronto nos "
          "comunicaremos contigo.\n";
  cout << "-----------------------------------------------"
          "--\n";
  irAMenuUsuario();
}
void consultaMantenimientos() {
  verEstadoMantenimientos();
  cout << "Escribe tu consulta sobre el mantenimiento que te interesa:\n";
  string consulta = "";
  cin.ignore();
  getline(cin, consulta);
  cout << "-----------------------------------------------"
          "--\n";
  cout << "Tu consulta se envio a uno de nuestros asesores pronto nos "
          "comunicaremos contigo.\n";
  cout << "-----------------------------------------------"
          "--\n";
  irAMenuUsuario();
}
void consultaQuejas() {
  verEstadoQuejas();
  cout << "Escribe tu consulta sobre la queja que te interesa:\n";
  string consulta = "";
  cin.ignore();
  getline(cin, consulta);
  cout << "-----------------------------------------------"
          "--\n";
  cout << "Tu consulta se envio a uno de nuestros asesores pronto nos "
          "comunicaremos contigo.\n";
  cout << "-----------------------------------------------"
          "--\n";
  menuUsuario(contactoActual);
}
void escribirConsultaEspecifica() {
  int opcion;
  do {
    cout << "Escoge sobre que es tu consulta:\n";
    cout << "1. Promociones\n";
    cout << "2. Status de Mantenimientos\n";
    cout << "3. Seguimiento de Quejas\n";
    cout << "4. volver\n";
    cin >> opcion;
  } while (opcion < 1 && opcion > 4);
  if(opcion == 4){
    menuUsuario(contactoActual);
  }
  else{
    switch (opcion) {
    case 1:
      consultaPromociones();
    case 2:
      consultaMantenimientos();
    case 3:
      verEstadoQuejas();
    }  
  }
}


void introducirQueja() {
  if(usuarioActual.planServicio.nombre.empty()){
  	cout << "-----------------------------------------------"
          "--\n";
  	cout << "No tienes ningun servicio del cual quejarte.";
  	cout << "-----------------------------------------------"
          "--\n";
  	menuUsuario(contactoActual);
  }
  cout << "Selecciona sobre que servicio es tu queja\n";
  int optionindex = 1;
  for (const auto &servicio : usuarioActual.planServicio.serviciosIncluidos) {
    cout << optionindex << ". " << servicio.nombre << ": "
         << servicio.descripcion << endl;
    optionindex++;
  }
  int opcion;
  cin >> opcion;
  cout << "Introduce tu queja: ";
  string queja = "";
  do{
  cin.ignore();
  getline(cin, queja);
  }while(queja.empty());
  string newid = generarID(8);
  usuarioActual.quejas.push_back({newid, "en Proceso", queja});
  cout << "-----------------------------------------------"
          "--\n";
  cout << "Queja registrada "
       << "con el ticket " << newid << "Gracias por tu feedback.\n";
  cout << "-----------------------------------------------"
          "--\n";
  irAMenuUsuario();
}

void verEstadoQuejas() {
  cout << "Tus quejas: \n";
  if (usuarioActual.quejas.size() > 0) {
    for (const auto &queja : usuarioActual.quejas) {
      cout << "ticket " << queja.id << " - " << queja.description
           << " - Estado: " << queja.status << endl;
    }
  } else {
    cout << "---------------------------------\n";
    cout << "No tienes quejas registradas.\n";
    cout << "---------------------------------\n";
  }
  irAMenuUsuario();
}

void quejaGeneral() {

  cout << "\n--- QUEJAS ---\n";
  cout << "1. Introducir una nueva queja\n";
  cout << "2. Regresar\n";

  int opcion;
  cin >> opcion;
  switch (opcion) {
  case 1:
    introducirQueja();
    break;
  case 2:
    // Regresar
    break;
  default:
    cout << "Opcion invalida.\n";
  }
}

void solicitarMantenimiento() {
  cout << "Selecciona el servicio para el cual deseas mantenimiento:\n";
  mostrarServicios();
  menuUsuario(contactoActual);
}

void verEstadoMantenimientos() {
  if (usuarioActual.mantenimientos.size() > 0) {
    for (const auto &mantenimiento : usuarioActual.mantenimientos) {
      cout << "El mantenimiento con ID: " << mantenimiento.id
           << " para tu servicio " << mantenimiento.nombreDelServicio
           << " esta " << mantenimiento.status << endl;
    }
  } else {
    cout << "No tienes ningun mantenimiento actualmente" << endl;
  }
}

void mantenimientoServicio() {

  cout << "\n--- MANTENIMIENTO DE SERVICIOS ---\n";
  cout << "1. Solicitar mantenimiento para un servicio\n";
  cout << "2. Ver estado de solicitudes de mantenimiento anteriores\n";
  cout << "3. Regresar\n";
  int opcion;
  cin >> opcion;
  switch (opcion) {
  case 1:
    solicitarMantenimiento();
    break;
  case 2:
    verEstadoMantenimientos();
    break;
  case 3:
    // Regresar
    break;
  default:
    cout << "Opcion invalida.\n";
  }
}

Usuario registrarUsuario() {
  vector<string> propiedadesDelUsuario = {"Nombre", "Apellido", "DPI", "Direccion", "NIT","Contacto", "Contrasena","Tipo de cliente (Particular/Empresarial)"};
  vector<string> respuestasDelUsuario = {};
   cout << "Por favor, ingresa la siguiente informacion:\n";
  for (const auto &propiedad : propiedadesDelUsuario) {
    string respuesta = "";
    do{
    cout << propiedad << ": ";
    getline(cin, respuesta);
    }while(respuesta.empty());
    respuestasDelUsuario.push_back(respuesta);
  }
  Usuario user = {respuestasDelUsuario[0],respuestasDelUsuario[1],respuestasDelUsuario[2],respuestasDelUsuario[3],respuestasDelUsuario[4],respuestasDelUsuario[5],respuestasDelUsuario[6],respuestasDelUsuario[7]};
  cout << "Registro exitoso.\n";
  irAMenuUsuario();
  return user;
};

bool iniciarSesion(string &contactoActual) {

  cout << "Ingreso de usuario registrado:\n";
  string contrasena =  "";
  cout << "Contacto: ";
  cin >> contactoActual;
  cout << "Contrasena: ";
  cin >> contrasena;

  if (usuarios.find(contactoActual) != usuarios.end() &&
      usuarios[contactoActual].contrasena == contrasena) {
    cout << "Inicio de sesion exitoso.\n";
    return true;
  } else {
    cout << "Usuario no encontrado o contrasena incorrecta.\n";
    return false;
  }
}

Usuario actualizarDatos(Usuario usuarioActual) {

  int opcion;

  do {
    cout << "\n------------------- ACTUALIZAR DATOS -------------------\n";
    cout << "1. Actualizar Nombre (" << usuarioActual.nombre << ")\n";
    cout << "2. Actualizar Apellido (" << usuarioActual.apellido << ")\n";
    cout << "3. Actualizar DPI (" << usuarioActual.DPI << ")\n";
    cout << "4. Actualizar Direccion (" << usuarioActual.direccion << ")\n";
    cout << "5. Actualizar NIT (" << usuarioActual.NIT << ")\n";
    cout << "6. Actualizar Contacto (" << usuarioActual.contacto << ")\n";
    cout << "7. Actualizar Contrasena\n";
    cout << "8. Actualizar Tipo de cliente (" << usuarioActual.tipoCliente
         << ")\n";
    cout << "9. Regresar\n";
    cout << "Elige una opcion: ";
    cin >> opcion;
    cin.ignore(); // Limpia el buffer

    string input = "";
    switch (opcion) {
    case 1:
      cout << "Nuevo nombre: ";
      getline(cin, input);
      if (!input.empty())
        usuarioActual.nombre = input;
      break;
    case 2:
      cout << "Nuevo apellido: ";
      getline(cin, input);
      if (!input.empty())
        usuarioActual.apellido = input;
      break;
    case 3:
      cout << "Nuevo DPI: ";
      getline(cin, input);
      if (!input.empty())
        usuarioActual.DPI = input;
      break;
    case 4:
      cout << "Nueva direccion: ";
      getline(cin, input);
      if (!input.empty())
        usuarioActual.direccion = input;
      break;
    case 5:
      cout << "Nuevo NIT: ";
      getline(cin, input);
      if (!input.empty())
        usuarioActual.NIT = input;
      break;
    case 6:
      cout << "Nuevo Contacto: ";
      getline(cin, input);
      if (!input.empty()) {
        usuarios.erase(usuarioActual.contacto); // Eliminar el anterior
        usuarioActual.contacto = input;         // Actualizar con el nuevo
      }
      break;
    case 7:
      cout << "Nueva contrasena: ";
      getline(cin, input);
      if (!input.empty())
        usuarioActual.contrasena = input;
      break;
    case 8:
      cout << "Nuevo tipo de cliente (Particular/Empresarial): ";
      getline(cin, input);
      if (!input.empty())
        usuarioActual.tipoCliente = input;
      break;
    case 9:
      cout << "Regresando...\n";
      break;
    default:
      cout << "Opcion invalida. Por favor intenta de nuevo.\n";
    }

  } while (opcion != 9);

  usuarios[usuarioActual.contacto] =
      usuarioActual; // Actualizar el mapa con el usuario modificado
  return usuarioActual;
}

void menuUsuario(string &contactoActual) {
  // verifica que no haya ya un usuario actual
  if (usuarioActual.nombre.empty()) {
    usuarioActual = usuarios[contactoActual];
  }
  int opcion;
  do {

    cout << "\n------------------- MENU REGISTRADO -------------------\n";
    cout << "1. Planes y Paquetes\n";
    cout << "2. Consulta\n";
    cout << "3. Queja\n";
    cout << "4. Mantenimiento de Servicio\n";
    cout << "5. Actualizar informacion personal\n";
    cout << "6. Actualiza tu Plan/Paquete\n";
    cout << "7. Cerrar sesion\n";
    cout << "Elige una opcion: ";
    cin >> opcion;
    cin.ignore(); // Limpia el buffer

    switch (opcion) {
    case 1:
      	mostrarTipoPlanes();
      break;
    case 2:
     	escribirConsultaEspecifica();
      break;
    case 3:
        quejaGeneral();
      break;
    case 4:
    	mantenimientoServicio();  
      break;
    case 5:
        usuarioActual = actualizarDatos(usuarioActual);
      break;
    case 6:
		mostrarDatosUsuario(usuarioActual);
      	cin.get(); // Espera hasta que el usuario presione Enter
      break;
    case 7:
      return;
    }
  } while (opcion != 8 && opcion != 9);
}

int main() {
	
  inicializarServiciosYPlanes();
  inicializarUsuarios();
  int opcion;
  do {
    cout << "\n------------------- MENU PRINCIPAL -------------------\n";
    cout << "1. Planes y Paquetes\n"; 
    cout << "2. Consulta\n";
    cout << "3. Iniciar sesion\n";
    cout << "4. Registrarse\n";
    cout << "5. Salir\n";
    cout << "Elige una opcion: ";
    cin >> opcion;
     if (cin.fail()) {
    // Si la entrada no es un número válido, se reinicia el estado de cin
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Entrada no valida. Por favor, ingrese un número válido.\n";
  }
	} while (opcion != 1 && opcion != 2 && opcion != 3 && opcion != 4 && opcion != 5);
    switch (opcion) {
    case 1:
      mostrarTipoPlanes();
      break;
    case 2:
      escribirConsultaGeneral();
      break;
    case 3:
      if (iniciarSesion(contactoActual)) {
        menuUsuario(contactoActual);
      }
      break;
    case 4:
      registrarUsuario();
      break;
    case 5:
      cout << "Gracias por usar nuestro sistema.\n";
      return 0;
    }

  return 0;
}