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
  int precio;
};

struct Plan {
  string nombre;
  string descripcion;
  vector<Servicio> serviciosIncluidos;
};

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
  string tipoCliente;
  string contrasena;
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
  cout << "------------------------------------\n";
  cout << "Oprime Cualquier tecla para continuar...\n";
  cout << "------------------------------------\n";
  cin.get();    // Esperamos a que el usuario presione Enter
  menuUsuario(contactoActual);
}

// creacion de un id random
string generarID(int longitud) {
  const std::string caracteres =
      "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  std::random_device rd;
  std::mt19937 generador(rd());
  std::uniform_int_distribution<int> distribucion(0, caracteres.size() - 1);

  std::string idGenerado;
  for (int i = 0; i < longitud; i++) {
    int indice = distribucion(generador);
    idGenerado += caracteres[indice];
  }
  return idGenerado;
}

void inicializarServiciosYPlanes() {
  // Definici�n de servicios
  servicios.push_back({"Internet", "Conexion a Internet de 100 Mbps", 1000});
  servicios.push_back(
      {"Telefono", "Linea telefonica con llamadas ilimitadas", 2000});
  servicios.push_back(
      {"Internet premium", "Conexion a Internet de 200 Mbps", 1499});
  servicios.push_back(
      {"Telefono", "Linea telefonica con llamadas ilimitadas internacionales",
       2200});
  // Definici�n de planes
  Plan planBasico = {
      "Plan Basico",
      "Plan b�sico con Internet y Tel�fono",
      {servicios[0], servicios[1]} // Servicios incluidos
  };
  Plan planPremium = {
      "Plan Premium",
      "Plan Premium con Internet ultra rapido y llamadas internacionales "
      "ilimitadas",
      {servicios[2], servicios[3]} // Servicios incluidos
  };
  planes.push_back(planBasico);
  planes.push_back(planPremium);
}

void inicializarUsuarios() {
  Usuario usuario1 = {"Juan",       "Perez",   "1234567890123",
                      "Calle 1",    "1234567", "contacto1",
                      "Particular", "pass1",   planes[0]};
  Usuario usuario2 = {"Maria",   "Gonzalez",  "9876543210987", "Calle 2",
                      "7654321", "contacto2", "Empresarial",   "pass2"};
  usuarios["contacto1"] = usuario1;
  usuarios["contacto2"] = usuario2;
}

Usuario UsuarioTemporal() {
  Usuario usuarioTemporal = {"User",       "Temp",   "0000000",
                             "Calle 0",    "000000", "contact0 0",
                             "Particular", "pass0",  {}};
  return usuarioTemporal;
}

void mostrarDatosUsuario(Usuario &usuario) {
  system("cls");
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
    const int planActual =
        encontrarIndiceDePlan(planes, usuario.planServicio.nombre);
    if (planActual != -1 && planActual < planes.size()) {
      int mejorplan = planActual + 1;
      cout << "-----------------------------------------------\n\n";
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
        system("cls");
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
          menuUsuario(contactoActual);
        }
      } else if (opcion == 2) {
        menuUsuario(contactoActual);
      }
    }
  }
}

int mostrarTelefoniaMovil() {
  int opcion;
  do {
    system("cls");
    cout << "\n--- TELEFONIA MOVIL ---\n";
    cout << "1. Plan de 100 minutos\n";
    cout << "2. Plan de 300 minutos con SMS ilimitados\n";
    cout << "3. Plan con 5GB de datos\n";
    cout << "4. Volver al men� de servicios\n";
    cout << "Elige una opci�n:";
    cin >> opcion;
    cin.ignore();

    switch (opcion) {
    case 1:
      cout << "Has elegido Plan de 100 minutos.\n";
      system("pause");
      break;
    case 2:
      cout << "Has elegido Plan de 300 minutos con SMS ilimitados.\n";
      system("pause");
      break;
    case 3:
      cout << "Has elegido Plan con 5GB de datos.\n";
      system("pause");
      break;
    case 4:
      return 0;
    }
  } while (opcion != 4);
  return 0;
}

int mostrarTelefoniaResidencial() {
  int opcion;

  do {
    system("cls");
    cout << "\n--- TELEFONIA RESIDENCIAL ---\n";
    cout << "1. Tel�fono solo\n";
    cout << "2. Tel�fono + Internet\n";
    cout << "3. Tel�fono + TV\n";
    cout << "4. Tel�fono + Internet + TV\n";
    cout << "5. Volver al men� de servicios\n";
    cout << "Elige una opcion: ";
    cin >> opcion;
    cin.ignore();

    switch (opcion) {
    case 1:
      cout << "Has elegido Tel�fono solo.\n";
      system("pause");
      break;
    case 2:
      cout << "Has elegido Tel�fono + Internet.\n";
      system("pause");
      break;
    case 3:
      cout << "Has elegido Tel�fono + TV.\n";
      system("pause");
      break;
    case 4:
      cout << "Has elegido Tel�fono + Internet + TV.\n";
      system("pause");
      break;
    case 5:
      return 0;
    }
  } while (opcion != 5);
  return 0;
}

int mostrarInternetMovil() {
  int opcion;
  do {
    system("cls");
    cout << "\n--- INTERNET MOVIL ---\n";
    cout << "1. Pre-pago 2GB\n";
    cout << "2. Post-pago 10GB\n";
    cout << "3. Volver al men� de servicios\n";
    cout << "Elige una opcion: ";
    cin >> opcion;
    cin.ignore();

    switch (opcion) {
    case 1:
      cout << "Has elegido Pre-pago 2GB.\n";
      system("pause");
      break;
    case 2:
      cout << "Has elegido Post-pago 10GB.\n";
      system("pause");
      break;
    case 3:
      return 0;
    }
  } while (opcion != 3);
  return 0;
}

int mostrarInternetResidencial() {
  int opcion;
  do {
    system("cls");
    cout << "\n--- INTERNET RESIDENCIAL ---\n";
    cout << "1. Internet 10Mbps\n";
    cout << "2. Internet 50Mbps + TV\n";
    cout << "3. Volver al men� de servicios\n";
    cout << "Elige una opcion: ";
    cin >> opcion;
    cin.ignore();

    switch (opcion) {
    case 1:
      cout << "Has elegido Internet 10Mbps.\n";
      system("pause");
      break;
    case 2:
      cout << "Has elegido Internet 50Mbps + TV.\n";
      system("pause");
      break;
    case 3:
      return 0;
    }
  } while (opcion != 3);
  return 0;
}

int mostrarTV() {
  int opcion;
  do {
    system("cls");
    cout << "\n--- TV ---\n";
    cout << "1. Paquete b�sico 100 canales\n";
    cout << "2. Paquete premium 200 canales + deportes\n";
    cout << "3. Volver al men� de servicios\n";
    cout << "Elige una opcion: ";
    cin >> opcion;
    cin.ignore();

    switch (opcion) {
    case 1:
      cout << "Has elegido Paquete b�sico 100 canales.\n";
      system("pause");
      break;
    case 2:
      cout << "Has elegido Paquete premium 200 canales + deportes.\n";
      system("pause");
      break;
    case 3:
      return 0;
    }
  } while (opcion != 3);
  return 0;
}

int mostrarServicios() {
  int opcion;
  do {
    system("cls");
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

int mostrarPlanes() {
  int opcion;
  do {
    system("cls");
    cout << "\n--- PLANES Y PAQUETES ---\n";
    cout << "Escoge el plan que quieras comprar: \n";
    int index = 1;
    for (const auto &plan : planes) {
      cout << index << ". " << plan.nombre << " - " << plan.descripcion << endl;
      index++;
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
    usuarioActual.planServicio = planes[indexplan];
    cout << "---------------------------------------\n";
    cout << "El plan: " << usuarioActual.planServicio.nombre
         << " ha sido activado en tu cuenta!" << endl;
    cout << "---------------------------------------\n";
    irAMenuUsuario();
  }
  return 0;
}

void escribirConsultaGeneral() {
  cout << "Escribe tu consulta a continuacion:\n";
  string consulta;
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
  string consulta;
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
  string consulta;
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
  string consulta;
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
void escribirConsultaEspecifica() {
  int opcion;
  do {
    cout << "Escoge sobre que es tu consulta:\n";
    cout << "1. Promociones\n";
    cout << "2. Status de Mantenimientos\n";
    cout << "3. Seguimiento de Quejas\n";
    cin >> opcion;
    switch (opcion) {
    case 1:
      consultaPromociones();
    case 2:
      consultaMantenimientos();
    case 3:
      verEstadoQuejas();
    }
  } while (opcion != 9);
  irAMenuUsuario();
}
int consultaGeneral() {
  int opcion;
  do {
    system("cls");
    cout << "\n--- CONSULTA GENERAL ---\n";
    cout << "1. Consulta general\n";
    cout << "2. Consulta Especifica\n";
    cout << "3. Volver al menu anterior\n";
    cout << "Elige una opcion: ";
    cin >> opcion;

    switch (opcion) {
    case 1:
      escribirConsultaGeneral();
      break;
    case 2:
      escribirConsultaEspecifica();
      break;
    case 3:
      return 0;
    }
  } while (opcion != 3);
  return 0;
}

void introducirQueja() {
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
  string queja;
  cin.ignore();
  getline(cin, queja);
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
    cout << "No tienes quejas registradas.\n";
  }
  irAMenuUsuario();
}

void quejaGeneral() {
  system("cls");
  cout << "\n--- QUEJAS ---\n";
  cout << "1. Introducir una nueva queja\n";
  cout << "2. Ver estado de quejas previas\n";
  cout << "3. Regresar\n";

  int opcion;
  cin >> opcion;
  switch (opcion) {
  case 1:
    introducirQueja();
    break;
  case 2:
    verEstadoQuejas();
    break;
  case 3:
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
  system("cls");
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
  system("cls");
  Usuario user;
  cout << "Por favor, ingresa la siguiente informacion:\n";
  cin.ignore();
  cout << "Nombre: ";
  getline(cin, user.nombre);
  cout << "Apellido: ";
  getline(cin, user.apellido);
  cout << "DPI: ";
  getline(cin, user.DPI);
  cout << "Direccion: ";
  getline(cin, user.direccion);
  cout << "NIT: ";
  getline(cin, user.NIT);
  cout << "Contacto: ";
  getline(cin, user.contacto);
  cout << "Contrasena: ";
  getline(cin, user.contrasena);
  cout << "Tipo de cliente (Particular/Empresarial): ";
  getline(cin, user.tipoCliente);
  usuarios[user.contacto] = user;
  cout << "Registro exitoso.\n";
  return user;
}

bool iniciarSesion(string &contactoActual) {
  system("cls");
  cout << "Ingreso de usuario registrado:\n";
  string contrasena;
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
  system("cls");
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

    string input;
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
    system("cls");
    cout << "\n------------------- MENU REGISTRADO -------------------\n";
    cout << "1. Servicios\n";
    cout << "2. Planes y Paquetes\n";
    cout << "3. Consulta\n";
    cout << "4. Queja\n";
    cout << "5. Mantenimiento de Servicio\n";
    cout << "6. Actualizar informacion personal\n";
    cout << "7. Mostrar mis datos\n";
    cout << "8. Cerrar sesion\n";
    cout << "9. Volver al menu principal\n";
    cout << "Elige una opcion: ";
    cin >> opcion;
    cin.ignore(); // Limpia el buffer

    switch (opcion) {
    case 1:
      mostrarServicios();
      break;
    case 2:
      mostrarPlanes();
      break;
    case 3:
      consultaGeneral();
      break;
    case 4:
      quejaGeneral();
      break;
    case 5:
      mantenimientoServicio();
      break;
    case 6:
      usuarioActual = actualizarDatos(usuarioActual);
      break;
    case 7:
      mostrarDatosUsuario(usuarioActual);
      cin.get(); // Espera hasta que el usuario presione Enter
      break;
    case 8:
      cout << "Cerrando sesion...\n";
      return;
    case 9:
      return;
    }
  } while (opcion != 8 && opcion != 9);
}

int main() {
  inicializarServiciosYPlanes();
  inicializarUsuarios();

  int opcion;
  do {
    system("cls");
    cout << "\n------------------- MENU PRINCIPAL -------------------\n";
    cout << "1. Iniciar sesion\n";
    cout << "2. Registrarse\n";
    cout << "3. Planes y Paquetes\n";
    cout << "4. Consulta\n";
    cout << "5. Salir\n";
    cout << "Elige una opcion: ";
    cin >> opcion;

    switch (opcion) {
    case 1:
      if (iniciarSesion(contactoActual)) {
        menuUsuario(contactoActual);
      }
      break;
    case 2:
      registrarUsuario();
      break;
    case 3:
      mostrarPlanes();
      break;
    case 4:
      consultaGeneral();
      break;
    case 5:
      cout << "Gracias por usar nuestro sistema.\n";
      return 0;
    }
  } while (opcion != 8);

  return 0;
}