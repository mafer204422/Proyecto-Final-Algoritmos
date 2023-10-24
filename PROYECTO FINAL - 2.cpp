#include <iostream>
#include <string>
#include <map>

using namespace std;

struct Usuario {
    string nombre;
    string apellido;
    string DPI;
    string direccion;
    string NIT;
    string contacto;
    string tipoCliente;
    string contrasena;
    string planServicio;
};

map<string, Usuario> usuarios;

void inicializarUsuarios() {
    Usuario usuario1 = {"Juan", "Perez", "1234567890123", "Calle 1", "1234567", "contacto1", "Particular", "pass1", ""};
    Usuario usuario2 = {"Maria", "Gonzalez", "9876543210987", "Calle 2", "7654321", "contacto2", "Empresarial", "pass2", ""};
    usuarios["contacto1"] = usuario1;
    usuarios["contacto2"] = usuario2;
}

int mostrarServicios() {
    int opcion;
    do {
        cout << "\n--- SERVICIOS DISPONIBLES ---\n";
        cout << "1. Telefonía móvil (plan de llamadas)\n";
        cout << "2. Telefonía residencial (Tel, Tel+Int, Tel+TV, Tel+Int+TV)\n";
        cout << "3. Internet móvil (pre-post pago)\n";
        cout << "4. Internet residencial (Int, Int+TV)\n";
        cout << "5. TV (TV)\n";
        cout << "6. Volver\n";
        cout << "Elige una opción: ";
        cin >> opcion;
        cin.ignore();  // Limpia el buffer

        switch(opcion) {
            case 1:
                cout << "Has elegido Telefonía móvil.\n";
                break;
            case 6:
                return 0;  // Retorna al menú anterior
        }
    } while(opcion != 6);
    return 0;
}

int mostrarPlanes() {
    int opcion;
    do {
        cout << "\n--- PLANES Y PAQUETES ---\n";
        cout << "1. Plan básico (1 servicio)\n";
        cout << "2. Plan premiun (2 servicios)\n";
        cout << "3. Plan VIP (3 servicios)\n";
        cout << "4. Volver\n";
        cout << "Elige una opción: ";
        cin >> opcion;
        cin.ignore();  // Limpia el buffer

        switch(opcion) {
            case 1:
                cout << "Has elegido Plan básico.\n";
                break;
            case 4:
                return 0;  // Retorna al menú anterior 
        }
    } while(opcion != 4);
    return 0;
}


int consultaGeneral() {
    int opcion;
    do {
        cout << "\n--- CONSULTA GENERAL ---\n";
        cout << "1. Información de servicios\n";
        cout << "2. Ayuda\n";
        cout << "3. Volver al menú anterior\n";
        cout << "Elige una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                cout << "Información sobre servicios.\n";
                break;
            case 2:
                cout << "Ayuda sobre consulta.\n";
                break;
            case 3:
                return 0;  
        }
    } while(opcion != 3);
    return 0;
}

void introducirQueja() {
    cout << "Introduce tu queja: ";
    string queja;
    cin.ignore();
    getline(cin, queja);
    cout << "Queja registrada. Gracias por tu feedback.\n";
}

void verEstadoQuejas() {
    cout << "\nQueja del 15 de Octubre de 2023: Resuelta\n";
    cout << "Queja del 10 de Octubre de 2023: En proceso\n";
}

void quejaGeneral() {
    cout << "\n--- QUEJAS ---\n";
    cout << "1. Introducir una nueva queja\n";
    cout << "2. Ver estado de quejas previas\n";
    cout << "3. Regresar\n";

    int opcion;
    cin >> opcion;
    switch(opcion) {
        case 1:
            introducirQueja();
            break;
        case 2:
            verEstadoQuejas();
            break;
        case 3:
            //Regresar
            break;
        default:
            cout << "Opción inválida.\n";
    }
}




void solicitarMantenimiento() {
    cout << "Selecciona el servicio para el cual deseas mantenimiento:\n";
    mostrarServicios();
    int opcion;
    cin >> opcion;
    cout << "Mantenimiento solicitado para el servicio seleccionado.\n";
}

void verEstadoMantenimientos() {
    cout << "\nMantenimiento solicitado el 20 de Octubre de 2023: En proceso\n";
    cout << "Mantenimiento solicitado el 15 de Octubre de 2023: Completado\n";
}

void mantenimientoServicio() {
    cout << "\n--- MANTENIMIENTO DE SERVICIO ---\n";
    cout << "1. Solicitar mantenimiento para un servicio\n";
    cout << "2. Ver estado de solicitudes de mantenimiento anteriores\n";
    cout << "3. Regresar\n";

    int opcion;
    cin >> opcion;
    switch(opcion) {
        case 1:
            solicitarMantenimiento();
            break;
        case 2:
            verEstadoMantenimientos();
            break;
        case 3:
            //Regresar
            break;
        default:
            cout << "Opción inválida.\n";
    }
}




Usuario registrarUsuario() {
    Usuario user;
    cout << "Por favor, ingresa la siguiente información:\n";
    cin.ignore();
    cout << "Nombre: ";
    getline(cin, user.nombre);
    cout << "Apellido: ";
    getline(cin, user.apellido);
    cout << "DPI: ";
    getline(cin, user.DPI);
    cout << "Dirección: ";
    getline(cin, user.direccion);
    cout << "NIT: ";
    getline(cin, user.NIT);
    cout << "Contacto: ";
    getline(cin, user.contacto);
    cout << "Contraseña: ";  
    getline(cin, user.contrasena);
    cout << "Tipo de cliente (Particular/Empresarial): ";
    getline(cin, user.tipoCliente);
    usuarios[user.contacto] = user;
    cout << "Registro exitoso.\n";
    return user;
}

bool iniciarSesion(string& contactoActual) {
    cout << "Ingreso de usuario registrado:\n";
    string contrasena;
    cout << "Contacto: ";
    cin >> contactoActual;
    cout << "Contraseña: ";
    cin >> contrasena;

    if (usuarios.find(contactoActual) != usuarios.end() && usuarios[contactoActual].contrasena == contrasena) {
        cout << "Inicio de sesión exitoso.\n";
        return true;
    } else {
        cout << "Usuario no encontrado o contraseña incorrecta.\n";
        return false;
    }
}



Usuario actualizarDatos(Usuario usuarioActual) {
    string input;
    cout << "Actualizar Nombre (" << usuarioActual.nombre << "): ";
    getline(cin, input);
    if (!input.empty()) usuarioActual.nombre = input;

    cout << "Actualizar Apellido (" << usuarioActual.apellido << "): ";
    getline(cin, input);
    if (!input.empty()) usuarioActual.apellido = input;

    cout << "Actualizar DPI (" << usuarioActual.DPI << "): ";
    getline(cin, input);
    if (!input.empty()) usuarioActual.DPI = input;

    cout << "Actualizar Dirección (" << usuarioActual.direccion << "): ";
    getline(cin, input);
    if (!input.empty()) usuarioActual.direccion = input;

    cout << "Actualizar NIT (" << usuarioActual.NIT << "): ";
    getline(cin, input);
    if (!input.empty()) usuarioActual.NIT = input;

    cout << "Actualizar Contacto (" << usuarioActual.contacto << "): ";
    getline(cin, input);
    if (!input.empty()) {
        usuarios.erase(usuarioActual.contacto);  // Eliminar el anterior
        usuarioActual.contacto = input;  // Actualizar con el nuevo
    }

    cout << "Actualizar Contraseña: ";
    getline(cin, input);
    if (!input.empty()) usuarioActual.contrasena = input;

    cout << "Actualizar Tipo de cliente (" << usuarioActual.tipoCliente << "): ";
    getline(cin, input);
    if (!input.empty()) usuarioActual.tipoCliente = input;

    usuarios[usuarioActual.contacto] = usuarioActual;
    cout << "Datos actualizados con éxito.\n";
    return usuarioActual;
}



void menuUsuario(string& contactoActual) {
	Usuario& usuarioActual = usuarios[contactoActual];
    int opcion;
    do {
        cout << "\n------------------- MENÚ REGISTRADO -------------------\n";
        cout << "1. Servicios\n";
        cout << "2. Planes y Paquetes\n";
        cout << "3. Consulta\n";
        cout << "4. Queja\n";
        cout << "5. Mantenimiento de Servicio\n";
        cout << "6. Actualizar información personal\n";
        cout << "7. Cerrar sesión\n";
        cout << "8. Volver al menú principal\n";
        cout << "Elige una opción: ";
        cin >> opcion;
        cin.ignore();  // Limpia el buffer

        switch(opcion) {
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
                cout << "Cerrando sesión...\n";
                return;
            case 8:
                return;
        }
    } while(opcion != 7 && opcion != 8);
}




int main() {
    inicializarUsuarios();

    int opcion;
    string contactoActual = "";

    do {
        cout << "\n------------------- MENÚ PRINCIPAL -------------------\n";
        cout << "1. Iniciar sesión\n";
        cout << "2. Registrarse\n";
        cout << "3. Servicios\n";
        cout << "4. Planes y Paquetes\n";
        cout << "5. Consulta\n";
        cout << "6. Salir\n";
        cout << "Elige una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                if (iniciarSesion(contactoActual)) {
                    menuUsuario(contactoActual);
                }
                break;
            case 2:
                registrarUsuario();
                break;
            case 3:
                mostrarServicios();
                break;
            case 4:
                mostrarPlanes();
                break;
            case 5:
                consultaGeneral();
                break;
            case 6:
                cout << "Gracias por usar nuestro sistema.\n";
                return 0;
        }
    } while(opcion != 8);

    return 0;
}

