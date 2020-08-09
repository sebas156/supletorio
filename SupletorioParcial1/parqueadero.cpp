#include "parqueadero.h"

parqueadero::parqueadero()
{
    //Inicializar celdas disponibles en cada nivel
    //--------------------------------------------
    for (int i = 1;i<=70;i++) {
        CeldasDisponiblesPiso1.push_back(i);
        CeldasDisponiblesPiso2.push_back(i);
        if(i<=50){
            CeldasDisponiblesPiso3.push_back(i);
            CeldasDisponiblesPiso4.push_back(i);
            CeldasDisponiblesPiso5.push_back(i);
        }
    }
    //--------------------------------------------
    LeerTarifas();
    LeerRegistroDeUsuarios();
    LlenarMasDatosDelConductor();
    DesactivarCeldasOcupadas();
}

bool parqueadero::BuscarUsuarioIngresado(string NombreUsuario, string Contrasena)
{
    for (int i =0 ;i<TodosLosUsuarios.size();i++) {
        if(TodosLosUsuarios[i].GetNombreUsuario()==NombreUsuario and TodosLosUsuarios[i].GetContasena()==Contrasena){
            PosicionUsuarioQueHaIniciadoSesion=i;
            return true;
        }
    }
    return false;
}

char parqueadero::MenuInterfazUsuario()
{
    char opcion;
    do{
        cout<<"Bienvenido: "<<TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].GetNombreUsuario()<<endl;
        cout<<"A. Registrar otro vehiculo a mi nombre. "<<endl;
        cout<<"B. Eliminar vehiculo a mi nombre. "<<endl;
        cout<<"C. Cambiar tipo de estacionamiento. "<<endl;
        cout<<"D. Mis vehiculos.  "<<endl;
        cout<<"E. Tarifas disponibles.  "<<endl;
        cout<<"F. Ingresar vehiculo al parqueadero. "<<endl;
        cout<<"G. Sacar vehiculo parqueadero. "<<endl;
        cout<<"H. Cerrar sesion. "<<endl;
        cin>>opcion;
        if(opcion != 'A' and opcion != 'B' and opcion != 'C' and opcion != 'D' and opcion != 'E' and opcion != 'F' and opcion != 'G'){
            cout<<"Opcion No Valida. "<<endl;
            system("CLS");
        }
    }while(opcion != 'A' and opcion != 'B' and opcion != 'C' and opcion != 'D' and opcion != 'E' and opcion != 'F' and opcion != 'G');
    return opcion;
}

bool parqueadero::RegistrarNuevoUsuario(string NuevoNombre, string contrasenaNueva)
{
    if(VerificarNombreIngresadoEstaEnArreglo(NuevoNombre)==false){
        usuario Auxiliar;
        Auxiliar.SetNombreUsuario(NuevoNombre);
        Auxiliar.SetContrasena(contrasenaNueva);
        TodosLosUsuarios.push_back(Auxiliar);
        return true;
    }
    else {
        cout<<"El nombre solicitado ya se encuentra en uso. "<<endl;
        return false;
    }
}

void parqueadero::AgregarVehiculoAmiNombre(string Tipo, string PlacaNueva)
{
    if(VerificarSiEsELmismoVehiculo(Tipo,PlacaNueva)==false){
        vehiculo Auxiliar;
        Auxiliar.SetTipoVehiculo(Tipo);
        Auxiliar.SetPlacaVehiculo(PlacaNueva);
        Auxiliar.SetTipoEstacionamiento('T');
        Auxiliar.SetCelda(-1);
        Auxiliar.SetPiso(-1);
        Auxiliar.SetBanderaParqueadero(0);
        Auxiliar.SetTipoDeCobro(-1);
        Auxiliar.Ingreso.hora=0;
        Auxiliar.Ingreso.minutos=0;
        Auxiliar.Ingreso.segundos=0;
        TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].VehiculosRegistrados.push_back(Auxiliar);
        cout<<"Vehiculo registraso exitosamente. "<<endl;
        char a;
        cout<<"Ingrese cualquier tecla: "<<endl;
        cin>>a;
    }
    else {
        cout<<"Lo sentimos pero creemos que ya tiene resgistrado este vehiculo. "<<endl;
        cout<<"Vuelve a intentarlo. "<<endl;
    }
}

void parqueadero::EliminarVehiculoAmiNombre(string Tipo, string placa)
{
    if(VerificarSiEsELmismoVehiculo(Tipo,placa)==true){
        for (auto i = TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].VehiculosRegistrados.begin();i!=TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].VehiculosRegistrados.end(); i++) {
            if((*i).GetPlacaVehiculo()==placa and (*i).GetTipoVehiculo()==Tipo){
                TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].VehiculosRegistrados.erase(i);
            }
        }
        RegistrarArchivoPorUsuario(TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].GetNombreUsuario()+".txt",PosicionUsuarioQueHaIniciadoSesion);
        cout<<"Vehiculo eliminado exitosamente. "<<endl;
        char a;
        cout<<"Ingrese cualquier tecla: "<<endl;
        cin>>a;
    }
    else {
        cout<<"Lo sentimos pero no es posible elimnar de su registro un vehiculo que no está registrado. "<<endl;
        cout<<"Vuelve a intentarlo. "<<endl;
    }
}

bool parqueadero::VerificarSiEsELmismoVehiculo(string Tipo, string PlacaNueva)
{
    for(auto i: TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].VehiculosRegistrados){
        if(i.GetPlacaVehiculo()==PlacaNueva and i.GetTipoVehiculo()==Tipo){
            return true;
        }
    }
    return false;
}

bool parqueadero::VerificarNombreIngresadoEstaEnArreglo(string ingresado)
{
    // Verifica si el nombre ingresado se encuentra entre los usuarios registrados.
    for(int i=0;i<TodosLosUsuarios.size();i++){
        if(TodosLosUsuarios[i].GetNombreUsuario()==ingresado){
            return true;
        }
    }
    return false;
}

void parqueadero::CambiarTipoDeEstacionamiento()
{
    cout<<"1. Carro. "<<endl;
    cout<<"2. Moto.  "<<endl;
    cout<<"3. Bicicleta. "<<endl;
    int seleccion;
    do{
        cout<<"Ingrese el tipo de vehiculo: "<<endl;
        cin>>seleccion;
        if(seleccion<1 or seleccion>3){
            cout<<"Opcion invalida. "<<endl;
        }

    }while(seleccion<1 or seleccion>3);
    string tipo;
    if(seleccion==1){
        tipo="Carro";
    }
    else if (seleccion==2) {
        tipo="Moto";
    }
    else {
        tipo="Bicicleta";
    }

    string placa;
    cout<<"Ingrese la placa: "<<endl;
    cin>>placa;
    if(VerificarSiEsELmismoVehiculo(tipo,placa)==true){
        list<vehiculo>::iterator i;
        for ( i = TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].VehiculosRegistrados.begin();i!=TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].VehiculosRegistrados.end();i++) {
            if((*i).GetTipoVehiculo()==tipo and (*i).GetPlacaVehiculo()==placa){
                break;
            }
        }
        char modo;
        do{
            cout<<"Ingrese el modo al cual va a pasar este vehiculo: (T o M) "<<endl;
            cout<<"T -> Temporal. "<<endl;
            cout<<"M -> Mensual. "<<endl;
            cout<<"En mayuscula. "<<endl;
            cin>>modo;
            if(modo != 'T' and modo!= 'M'){
                cout<<"Solo existe dos modos. "<<endl;
            }
        }while(modo != 'T' and modo!= 'M');

        if(modo=='M'){
            if((*i).GetTipoEstacionamiento()=='M'){
                if(tipo=="Carro")
                    cout<<"El "<<tipo<<" con placa "<<placa<<" ya tenía este modo. "<<endl;
                else
                    cout<<"La "<<tipo<<" con placa "<<placa<<" ya tenía este modo. "<<endl;
            }
            else {
                int dinero;
                cout<<"Como usted va a pasar al modo mensual necesita realizar el pago ya. "<<endl;
                cout<<"La cantidad de dinero a pagar es: "<<TiposDeVehiculos[tipo].at(2);
                do{
                    cout<<"Ingrese la cantidad de dinero: "<<endl;
                    cin>>dinero;

                }while(dinero<TiposDeVehiculos[tipo].at(2));
                int cambio = dinero -TiposDeVehiculos[tipo].at(2);
                auto t = std::time(nullptr); // Obtiene la fecha y la hora.
                auto tm = *std::localtime(&t);
                ostringstream oss;
                oss << put_time(&tm, "%d-%m-%Y %H-%M-%S");
                auto str = oss.str();
                str= "Fecha: "+ str.substr(0,str.find(" "))+" Hora: "+ str.substr(str.find(" ")+1,str.size()-str.find(" "));
                string registar = str + " "+TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].GetNombreUsuario()+ " " + tipo + placa + (*i).GetTipoEstacionamiento()+" - > "+ modo + to_string(dinero)+ " " + to_string(cambio);
                if((*i).GetPiso()==1){

                    MovimientoRegistrar("nivel1.txt",registar);
                }
                else if ((*i).GetPiso()==2) {
                    MovimientoRegistrar("nivel2.txt",registar);
                }
                else if ((*i).GetPiso()==3) {
                    MovimientoRegistrar("nivel3.txt",registar);
                }
                else if ((*i).GetPiso()==4) {
                    MovimientoRegistrar("nivel4.txt",registar);
                }
                else {
                    MovimientoRegistrar("nivel5.txt",registar);
                }
                cout<<endl;
                cout<<"Su cambio es: "<<endl;
                cambio_diniero(&cambio);
                cout<<"Con un resto de: "<<cambio<<endl;
                (*i).SetTipoEstacionamiento('M');
                (*i).SetTipoDeCobro(3);
            }
        }
        else {
            if((*i).GetTipoEstacionamiento()=='T'){
                if(tipo=="Carro")
                    cout<<"El "<<tipo<<" con placa "<<placa<<" ya tenía este modo. "<<endl;
                else
                    cout<<"La "<<tipo<<" con placa "<<placa<<" ya tenía este modo. "<<endl;
            }
            else {
                auto t = std::time(nullptr); // Obtiene la fecha y la hora.
                auto tm = *std::localtime(&t);
                ostringstream oss;
                oss << put_time(&tm, "%d-%m-%Y %H-%M-%S");
                auto str = oss.str();
                str= "Fecha: "+ str.substr(0,str.find(" "))+" Hora: "+ str.substr(str.find(" ")+1,str.size()-str.find(" "));
                string registar = str + " "+TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].GetNombreUsuario()+ " " + tipo + placa + (*i).GetTipoEstacionamiento()+" - > "+ modo + to_string(0)+ " " + to_string(0);
                if((*i).GetPiso()==1){

                    MovimientoRegistrar("nivel1.txt",registar);
                }
                else if ((*i).GetPiso()==2) {
                    MovimientoRegistrar("nivel2.txt",registar);
                }
                else if ((*i).GetPiso()==3) {
                    MovimientoRegistrar("nivel3.txt",registar);
                }
                else if ((*i).GetPiso()==4) {
                    MovimientoRegistrar("nivel4.txt",registar);
                }
                else {
                    MovimientoRegistrar("nivel5.txt",registar);
                }
                (*i).SetTipoEstacionamiento('T');
                (*i).SetTipoDeCobro(-1);
            }
        }

        cout<<"Transaccion realizada con exito. "<<endl;
    }
    else {
        cout<<"Lo sentimos pero el auto ingresado no se encuentra en nuestra base de datos. "<<endl;
    }

}

void parqueadero::MisVehiculos()
{
    cout<<"Tipo       Placa           Tipo de estacionamiento         Piso           Celda"<<endl;
    for(auto i : TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].VehiculosRegistrados){
        cout<<i.GetTipoVehiculo()<<"           "<<i.GetPlacaVehiculo()<<"            "<<i.GetTipoEstacionamiento()<<"           "<<i.GetPiso()<<"             "<<i.GetCelda()<<"      "<<endl;
    }
}

char parqueadero::MenuInterfazAdministrador()
{
    char opcion;
    do{
        cout<<"A. Porcentaje Ocupado de Cada de uno de los Pisos. "<<endl;
        cout<<"B. Registro de los vehiculos por nivel. "<<endl;
        cout<<"C. Mostrar Tabla de Tarifas Actual. "<<endl;
        cout<<"D. Crear o Cambiar la tabla de tarifas actual. "<<endl;
        cout<<"E. Reporte por nivel en lo que va del dia.  "<<endl;
        cout<<"F. Reporte total en lo que va del dia. "<<endl;
        cout<<"G. Cerrar sesion. "<<endl;
        cin>>opcion;
        if(opcion != 'A' and opcion != 'B' and opcion != 'C' and opcion != 'D' and opcion != 'E' and opcion != 'F' and opcion != 'G'){
            cout<<"Opcion No Valida. "<<endl;
            system("CLS");
        }
    }while(opcion != 'A' and opcion != 'B' and opcion != 'C' and opcion != 'D' and opcion != 'E' and opcion != 'F' and opcion != 'G');
    return opcion;
}

void parqueadero::ArchivoAdministrador()
{
    ifstream ArchiAdmini("redo.txt");
    if(ArchiAdmini.fail())
        cout<<"El archivo NO pudo abrirse... redo.txt"<<endl;
    else {
        string renglon;
        getline(ArchiAdmini,renglon);
        int posicionComa=renglon.find(",");
        UsuarioAdmi=renglon.substr(0,posicionComa);
        ContrasenaAdmni=renglon.substr(posicionComa+1,renglon.size()-posicionComa);
    }
    ArchiAdmini.close();
}

void parqueadero::PorcentajeOcupadoDeCadaUnoDelosPisos()
{
    int Ocupados,aproximar;
    float PorcentajeOcupado;
    cout<<"Nivel        Celdas Ocupadas         Celdas Totales            Porcentaje Ocupado            Tipo Vehiculo.        "<<endl;
    Ocupados=CeldasTotalesP12-CeldasDisponiblesPiso1.size();
    PorcentajeOcupado=(Ocupados/CeldasTotalesP12)*100;
    aproximar=PorcentajeOcupado*100;
    PorcentajeOcupado=aproximar;
    PorcentajeOcupado/=100;
    cout<<"  1            "<<Ocupados<<"          "<<CeldasTotalesP12<<"            "<<PorcentajeOcupado<<"         Moto          "<<endl;
    Ocupados=CeldasTotalesP12-CeldasDisponiblesPiso2.size();
    PorcentajeOcupado=(Ocupados/CeldasTotalesP12)*100;
    aproximar=PorcentajeOcupado*100;
    PorcentajeOcupado=aproximar;
    PorcentajeOcupado/=100;
    cout<<"  2            "<<Ocupados<<"          "<<CeldasTotalesP12<<"            "<<PorcentajeOcupado<<"         Moto          "<<endl;
    Ocupados=CeldasTotalesP345-CeldasDisponiblesPiso3.size();
    PorcentajeOcupado=(Ocupados/CeldasTotalesP345)*100;
    aproximar=PorcentajeOcupado*100;
    PorcentajeOcupado=aproximar;
    PorcentajeOcupado/=100;
    cout<<"  3            "<<Ocupados<<"          "<<CeldasTotalesP345<<"            "<<PorcentajeOcupado<<"         Carro          "<<endl;
    Ocupados=CeldasTotalesP345-CeldasDisponiblesPiso4.size();
    PorcentajeOcupado=(Ocupados/CeldasTotalesP345)*100;
    aproximar=PorcentajeOcupado*100;
    PorcentajeOcupado=aproximar;
    PorcentajeOcupado/=100;
    cout<<"  4            "<<Ocupados<<"          "<<CeldasTotalesP345<<"            "<<PorcentajeOcupado<<"         Carro          "<<endl;
    Ocupados=CeldasTotalesP345-CeldasDisponiblesPiso5.size();
    PorcentajeOcupado=(Ocupados/CeldasTotalesP345)*100;
    aproximar=PorcentajeOcupado*100;
    PorcentajeOcupado=aproximar;
    PorcentajeOcupado/=100;
    cout<<"  5            "<<Ocupados<<"          "<<CeldasTotalesP345<<"            "<<PorcentajeOcupado<<"       Bicicleta          "<<endl;
}

void parqueadero::RegistroDeVehiculosPorNivel(int NivelSelecccionado)
{
    cout<<"Nivel: "<<NivelSelecccionado<<endl;
    cout<<"Celda                Placa             Hora de ingreso        Tipo de estacionamiento         "<<endl;
    for (auto Iterador1 : TodosLosUsuarios) {
        for(auto Iterador2:Iterador1.VehiculosRegistrados){
            if(Iterador2.GetPiso()==NivelSelecccionado and Iterador2.GetBanderaParqueadero()==1){
                cout<<Iterador2.GetCelda()<<"      "<<Iterador2.GetPlacaVehiculo()<<"     "<<Iterador2.Ingreso.hora<<":"<<Iterador2.Ingreso.minutos<<":"<<Iterador2.Ingreso.segundos<<"          "<<Iterador2.GetTipoEstacionamiento()<<"      "<<endl;
            }
        }
    }
}

void parqueadero::CambiarCrearTabladeTarifas()
{
    cout<<"Carro: "<<endl;
    cout<<"Ingrese el cobro por hora: "<<endl;
    cin>>TiposDeVehiculos["Carro"].at(0);
    cout<<"Ingrese el cobro por dia: "<<endl;
    cin>>TiposDeVehiculos["Carro"].at(1);
    cout<<"Ingrese el cobro por mes: "<<endl;
    cin>>TiposDeVehiculos["Carro"].at(2);
    cout<<"Moto: "<<endl;
    cout<<"Ingrese el cobro por hora: "<<endl;
    cin>>TiposDeVehiculos["Moto"].at(0);
    cout<<"Ingrese el cobro por dia: "<<endl;
    cin>>TiposDeVehiculos["Moto"].at(1);
    cout<<"Ingrese el cobro por mes: "<<endl;
    cin>>TiposDeVehiculos["Moto"].at(2);
    cout<<"Bicicleta: "<<endl;
    cout<<"Ingrese el cobro por hora: "<<endl;
    cin>>TiposDeVehiculos["Bicicleta"].at(0);
    cout<<"Ingrese el cobro por dia: "<<endl;
    cin>>TiposDeVehiculos["Bicicleta"].at(1);
    cout<<"Ingrese el cobro por mes: "<<endl;
    cin>>TiposDeVehiculos["Bicicleta"].at(2);
}

void parqueadero::ReportePorNivelEnLoQueVaDelDia(string NombreArchivo)
{
    ifstream ArchivoNivel(NombreArchivo);
    if(ArchivoNivel.fail())
        cout<<"Error al abrir el archivo. "<<NombreArchivo<<"."<<endl;
    else {
        while (!ArchivoNivel.eof()) {
            string renglon;
            getline(ArchivoNivel,renglon);
            cout<<renglon<<endl;
        }
    }
    ArchivoNivel.close();
}

void parqueadero::ReporteTotalEnLoQueVaDelDia()
{
    for (int i=1;i<=5;i++) {
        if(i==1){
            cout<<"Nivel 1: "<<endl;
            ReportePorNivelEnLoQueVaDelDia("nivel1.txt");
        }
        else if (i==2) {
            cout<<"Nivel 2: "<<endl;
            ReportePorNivelEnLoQueVaDelDia("nivel2.txt");
        }
        else if (i==3) {
            cout<<"Nivel 3: "<<endl;
            ReportePorNivelEnLoQueVaDelDia("nivel3.txt");
        }
        else if (i==4) {
            cout<<"Nivel 4: "<<endl;
            ReportePorNivelEnLoQueVaDelDia("nivel4.txt");
        }
        else {
            cout<<"Nivel 5: "<<endl;
            ReportePorNivelEnLoQueVaDelDia("nivel5.txt");
        }
    }
}

char parqueadero::MenoPricipal()
{
    char opcion;
    do{
        cout<<" A. Ingresar como Administrador. "<<endl;
        cout<<" B. Ingresar como usuario. "<<endl;
        cout<<" C. Crear una cuenta.      "<<endl;
        cout<<" D. Salir. "<<endl;
        cin>>opcion;
        if(opcion != 'A' and opcion != 'B' and opcion != 'C' and opcion != 'D'){
            cout<<"Opcion invalida. "<<endl;
            system("CLS");
        }

    }while(opcion != 'A' and opcion != 'B' and opcion != 'C' and opcion != 'D');
    return opcion;
}

void parqueadero::LeerRegistroDeUsuarios()
{
    // Lee del archivo UsuariosRegistrados los usuarios. Esto para extraer su usuario y contrasena.
    ifstream archivoUsuarios("UsuariosRegistrados.txt");

    if(archivoUsuarios.fail())
        cout<<"Error al abrir el archivo. LeerRegistroUsuairos"<<endl;
    else {
        while (!archivoUsuarios.eof()) {
            string renglon="";
            getline(archivoUsuarios,renglon);
            if(renglon!="")
                LlenarConUsuariosRegistrados(renglon);
        }
    }

    archivoUsuarios.close();
}

int parqueadero::StringANumero(string cadena)
{
    //Convierte una cadena de caracteres al numero que está representando.
    int acum=0;
    for(int i=0; i<cadena.size();i++){
        acum+=cadena[i]-48;
        acum*=10;
    }
    acum/=10;
    return acum;
}

void parqueadero::LlenarConUsuariosRegistrados(string UsuarioContrasena)
{
    // Lo que hace esta funcion es tomar el Usuario y Contrasena del archivo y lo añade al vector usuarios registrados.
    usuario Auxiliar;
    int aux;
    string Usuario;
    string Paswoord;
    aux=UsuarioContrasena.find(",");
    Usuario=UsuarioContrasena.substr(0,aux);
    Paswoord=UsuarioContrasena.substr(aux+1,UsuarioContrasena.size()-aux);
    Auxiliar.SetNombreUsuario(Usuario);
    Auxiliar.SetContrasena(Paswoord);
    TodosLosUsuarios.push_back(Auxiliar);
}

void parqueadero::VisualizarTarifas()
{
    if(SinpreciosTodavia()==false){
        cout<<"TIPO              HORA             DIA            MES      "<<endl;
        for(auto i : TiposDeVehiculos){
            cout<<i.first<<"         "<<i.second.at(0)<<"            "<<i.second.at(1)<<"         "<<i.second.at(2)<<endl;
        }
    }
    else {
        cout<<"Aun no hay una tarifa disponible. "<<endl;
    }
}

bool parqueadero::SinpreciosTodavia()
{
    for (auto i: TiposDeVehiculos) {
        if(i.second.at(0)==0 or i.second.at(0)==0 or i.second.at(0)==0)
            return false;
    }
    return true;
}

void parqueadero::LeerTarifas()
{
    ifstream archivoTarifas("tarifas.txt");

    if(archivoTarifas.fail())
        cout<<"Error al abrir el archivo. LeerRegistroUsuairos"<<endl;
    else {
        while (!archivoTarifas.eof()) {
            string renglon="";
            getline(archivoTarifas,renglon);
            if(renglon!="")
                DescomponerInformacionTarifas(renglon);
        }
    }

    archivoTarifas.close();
}

void parqueadero::DescomponerInformacionTarifas(string renglon)
{
    int PosicionComa=renglon.find(",");
    string NombreTipo=renglon.substr(0,PosicionComa);
    renglon=renglon.substr(PosicionComa+1, renglon.size()-PosicionComa);
    PosicionComa=renglon.find(",");
    int PorHora=StringANumero(renglon.substr(0,PosicionComa));
    renglon=renglon.substr(PosicionComa+1, renglon.size()-PosicionComa);
    PosicionComa=renglon.find(",");
    int PorDia=StringANumero(renglon.substr(0,PosicionComa));
    renglon=renglon.substr(PosicionComa+1, renglon.size()-PosicionComa);
    int PorMes=StringANumero(renglon);
    TiposDeVehiculos.insert({NombreTipo,{PorHora,PorDia,PorMes}});

}

void parqueadero::RegistrarTarifa()
{
    ofstream archivoTarifas("tarifas.txt");
    if(archivoTarifas.fail())
        cout<<"Error al abrir el archivo. LeerRegistroUsuairos"<<endl;
    else {
        for(auto i: TiposDeVehiculos){
            archivoTarifas<<i.first<<","<<i.second.at(0)<<","<<i.second.at(1)<<","<<i.second.at(2)<<endl;
        }
    }

    archivoTarifas.close();
}

void parqueadero::RegistrarUsuariosActuales()
{
    // Registra en el archivo UsuariosRegistrados los usuarios. Esto para extraer su usuario y contrasena.
    ofstream archivoUsuarios("UsuariosRegistrados.txt");

    if(archivoUsuarios.fail())
        cout<<"Error al abrir el archivo. LeerRegistroUsuairos"<<endl;
    else {
        for(auto i: TodosLosUsuarios){
            archivoUsuarios<<i.GetNombreUsuario()<<","<<i.GetContasena()<<endl;
        }
    }

    archivoUsuarios.close();
}

void parqueadero::RegistrarArchivoPorUsuario(string usuario, int posicionActual)
{
    ofstream archivoUsuarios(usuario);

    if(archivoUsuarios.fail())
        cout<<"Error al abrir el archivo. LeerRegistroUsuairos"<<endl;
    else {
        for(auto i: TodosLosUsuarios[posicionActual].VehiculosRegistrados){
            archivoUsuarios<<i.GetTipoVehiculo()<<","<<i.GetPlacaVehiculo()<<","<<i.GetTipoEstacionamiento()<<","<<i.GetPiso()<<","<<i.GetCelda()<<","<<i.GetBanderaParqueadero()<<","<<i.GetTipoDeCobro()<<","<<i.Ingreso.hora<<","<<i.Ingreso.minutos<<","<<i.Ingreso.segundos<<endl;
        }
    }

    archivoUsuarios.close();
}

void parqueadero::DesactivarCeldasOcupadas()
{
    for (auto Iterador1: TodosLosUsuarios) {
        for(auto Iterador2: Iterador1.VehiculosRegistrados){
            if(Iterador2.GetPiso()==1){
                for (auto IteradorLista1=CeldasDisponiblesPiso1.begin();IteradorLista1!=CeldasDisponiblesPiso1.end();IteradorLista1++) {
                    if(*IteradorLista1==Iterador2.GetCelda()){
                        CeldasDisponiblesPiso1.erase(IteradorLista1);
                    }
                }
            }
            else if (Iterador2.GetPiso()==2) {
                for (auto IteradorLista2=CeldasDisponiblesPiso2.begin();IteradorLista2!=CeldasDisponiblesPiso2.end();IteradorLista2++) {
                    if(*IteradorLista2==Iterador2.GetCelda()){
                        CeldasDisponiblesPiso2.erase(IteradorLista2);
                    }
                }
            }
            else if (Iterador2.GetPiso()==3) {
                for (auto IteradorLista3=CeldasDisponiblesPiso1.begin();IteradorLista3!=CeldasDisponiblesPiso3.end();IteradorLista3++) {
                    if(*IteradorLista3==Iterador2.GetCelda()){
                        CeldasDisponiblesPiso3.erase(IteradorLista3);
                    }
                }
            }
            else if (Iterador2.GetPiso()==4) {
                for (auto IteradorLista4=CeldasDisponiblesPiso4.begin();IteradorLista4!=CeldasDisponiblesPiso4.end();IteradorLista4++) {
                    if(*IteradorLista4==Iterador2.GetCelda()){
                        CeldasDisponiblesPiso4.erase(IteradorLista4);
                    }
                }
            }
            else {
                for (auto IteradorLista5=CeldasDisponiblesPiso5.begin();IteradorLista5!=CeldasDisponiblesPiso5.end();IteradorLista5++) {
                    if(*IteradorLista5==Iterador2.GetCelda()){
                        CeldasDisponiblesPiso5.erase(IteradorLista5);
                    }
                }
            }
        }
    }
}

void parqueadero::LlenarMasDatosDelConductor()
{
    for (int i=0 ; i< TodosLosUsuarios.size();i++) {
        AccederDatosConductor(TodosLosUsuarios[i].GetNombreUsuario()+".txt",i);
    }
}

void parqueadero::AccederDatosConductor(string NombreArchivo, int PosiconActual)
{
    // Lee el documento.
    ifstream archivoUsuarios(NombreArchivo);

    if(archivoUsuarios.fail())
        cout<<"Error al abrir el archivo. LeerRegistroUsuairos"<<endl;
    else {
        while (!archivoUsuarios.eof()) {
            string renglon="";
            getline(archivoUsuarios,renglon);
            if(renglon!="")
                DescomponerInformacionUsuario(renglon, PosiconActual);
        }
    }

    archivoUsuarios.close();
}

void parqueadero::DescomponerInformacionUsuario(string renglon, int PosicionActual)
{
    // Extrae la informacion del archivo.
    vehiculo Auxiliar;
    int PosicionComa=renglon.find(",");
    string ExtraerTipo=renglon.substr(0,PosicionComa);
    renglon=renglon.substr(PosicionComa+1, renglon.size()-PosicionComa);
    PosicionComa=renglon.find(",");
    string ExtraerPlaca=renglon.substr(0,PosicionComa);
    renglon=renglon.substr(PosicionComa+1, renglon.size()-PosicionComa);
    PosicionComa=renglon.find(",");
    string ExtraerTiempo=renglon.substr(0,PosicionComa);
    renglon=renglon.substr(PosicionComa+1, renglon.size()-PosicionComa);
    PosicionComa=renglon.find(",");
    int ExtraerPiso=StringANumero(renglon.substr(0,PosicionComa));
    renglon=renglon.substr(PosicionComa+1, renglon.size()-PosicionComa);
    PosicionComa=renglon.find(",");
    int ExtraerCelda=StringANumero(renglon.substr(0,PosicionComa));
    renglon=renglon.substr(PosicionComa+1, renglon.size()-PosicionComa);
    PosicionComa=renglon.find(",");
    int ExtraerBanderaParqueadero=StringANumero(renglon.substr(0,PosicionComa));
    renglon=renglon.substr(PosicionComa+1, renglon.size()-PosicionComa);
    PosicionComa=renglon.find(",");
    int ExtraerTipoDeCobro=StringANumero(renglon.substr(0,PosicionComa));
    renglon=renglon.substr(PosicionComa+1, renglon.size()-PosicionComa);
    PosicionComa=renglon.find(",");
    int ExtraerHora=StringANumero(renglon.substr(0,PosicionComa));
    renglon=renglon.substr(PosicionComa+1, renglon.size()-PosicionComa);
    PosicionComa=renglon.find(",");
    int ExtraerMinutos=StringANumero(renglon.substr(0,PosicionComa));
    renglon=renglon.substr(PosicionComa+1, renglon.size()-PosicionComa);
    PosicionComa=renglon.find(",");
    int ExtraerSegundos=StringANumero(renglon.substr(0,PosicionComa));
    renglon=renglon.substr(PosicionComa+1, renglon.size()-PosicionComa);
    PosicionComa=renglon.find(",");
    Auxiliar.SetPiso(ExtraerPiso);
    Auxiliar.SetTipoEstacionamiento(ExtraerTiempo[0]);
    Auxiliar.SetTipoVehiculo(ExtraerTipo);
    Auxiliar.SetPlacaVehiculo(ExtraerPlaca);
    Auxiliar.SetBanderaParqueadero(ExtraerBanderaParqueadero);
    Auxiliar.SetTipoDeCobro(ExtraerTipoDeCobro);
    Auxiliar.Ingreso.hora=ExtraerHora;
    Auxiliar.Ingreso.minutos=ExtraerMinutos;
    Auxiliar.Ingreso.segundos=ExtraerSegundos;
    TodosLosUsuarios[PosicionActual].VehiculosRegistrados.push_back(Auxiliar);

}

void parqueadero::cambio_diniero(int *dinero){
    cout<<"Billetes de 50 000: "<<*dinero/50000<<endl;
    *dinero=*dinero%50000;
    cout<<"Billetes de 20 000: "<<*dinero/20000<<endl;
    *dinero=*dinero%20000;
    cout<<"Billetes de 10 000: "<<*dinero/10000<<endl;
    *dinero=*dinero%10000;
    cout<<"Billetes de 5000: "<<*dinero/5000<<endl;
    *dinero=*dinero%5000;
    cout<<"Billetes de 2000: "<<*dinero/2000<<endl;
    *dinero=*dinero%2000;
    cout<<"Billetes de 1000: "<<*dinero/1000<<endl;
    *dinero=*dinero%1000;
    cout<<"Monedas de 500: "<<*dinero/500<<endl;
    *dinero=*dinero%500;
    cout<<"Monedas de 200: "<<*dinero/200<<endl;
    *dinero=*dinero%200;
    cout<<"Monedas de 100: "<<*dinero/100<<endl;
    *dinero=*dinero%100;
    cout<<"Monedas de 50: "<<*dinero/50<<endl;
    *dinero=*dinero%50;
}

void parqueadero::MovimientoRegistrar(string archivo, string movimiento)
{
    ofstream ArchivoActualizar(archivo,ios::app);
    if(ArchivoActualizar.fail())
        cout<<"Error al abrir el archivo. Regristrar movimeinto. "<<archivo<<endl;
    else {
        ArchivoActualizar<<movimiento<<endl;
    }
    ArchivoActualizar.close();
}

void parqueadero::IngresarVehiculoAlParqueadero()
{
    int seleccion;
    cout<<"Selecciona el tipo de vehiculo e ingresa la placa del mismo: "<<endl;
    do{
        cout<<"1. Carro. "<<endl;
        cout<<"2. Moto.  "<<endl;
        cout<<"3. Bicicleta. "<<endl;
        cin>>seleccion;
        if(seleccion<1 and seleccion>3)
            cout<<"Opcion invalida. "<<endl;
    }while(seleccion<1 and seleccion>3);

    string tipo;

    if(seleccion==1){
        tipo = "Carro";
    }
    else if (seleccion==2) {
        tipo="Moto";
    }
    else {
        tipo="Bicicleta";
    }

    string matricula;
    cout<<"Ingrese la placa del vehiculo: "<<endl;
    cin>>matricula;
    if(VerificarSiEsELmismoVehiculo(tipo,matricula)==true){
        list<vehiculo>::iterator i;
        for ( i = TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].VehiculosRegistrados.begin();i!=TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].VehiculosRegistrados.end();i++) {
            if((*i).GetTipoVehiculo()==tipo and (*i).GetPlacaVehiculo()==matricula){
                break;
            }
        }
        if((*i).GetBanderaParqueadero()==1){
            cout<<"Lo sentimos pero el vehiculo ya se encuentra en el parqueadero. "<<endl;
        }
        else {
            if((*i).GetTipoEstacionamiento()=='T'){
                int tipoaux;
                if(tipo=="Carro"){
                    int PisoSeleccionar;
                    do{
                        cout<<"Por favor, ingrese el piso (3 o 4): "<<endl;
                        cin>>PisoSeleccionar;
                        if(PisoSeleccionar != 3 and PisoSeleccionar != 4)
                            cout<<"Piso invalido para el tipo de vehiculo. "<<endl;

                    }while(PisoSeleccionar != 3 and PisoSeleccionar != 4);

                    if(PisoSeleccionar==3){
                        cout<<"Celdas disponibles: "<<endl;
                        for(int iterador:CeldasDisponiblesPiso3){
                            cout<<iterador<<" ";
                        }
                        cout<<endl;
                    }
                    else {
                        cout<<"Celdas disponibles: "<<endl;
                        for(int iterador:CeldasDisponiblesPiso4){
                            cout<<iterador<<" ";
                        }
                        cout<<endl;
                    }
                }
                else if (tipo == "Moto") {

                }
                else {

                }
                do{
                    cout<<"Ingrese la clase de cobro que se le hara: "<<endl;
                    cout<<"1. Quiero que me cobren por hora. "<<endl;
                    cout<<"2. Quiero que me cobren pir dias. "<<endl;
                    cout<<"Recuerda que si decides que el cobro se te haga por días. No podras sacar el mismo hasta que se cumpla al menos un dia. "<<endl;
                    cin>>tipoaux;
                    if(tipoaux != 1 and tipoaux != 2){
                        cout<<"Solo hay dos opciones. "<<endl;
                    }
                }while(tipoaux != 1 and tipoaux != 2);

                (*i).SetTipoEstacionamiento(tipoaux);
                (*i).SetBanderaParqueadero(1);
                //------------------------------------------
                // Extrae el tiempo
                time_t currentTime = time(NULL);
                time(&currentTime);
                struct tm *myTime = localtime(&currentTime);
                //------------------------------------------
                (*i).Ingreso.hora=myTime->tm_hour;
                (*i).Ingreso.minutos=myTime->tm_min;
                (*i).Ingreso.segundos=myTime->tm_sec;

                //_______________________________
                auto t = std::time(nullptr); // Obtiene la fecha y hora para el registro.
                auto tm = *std::localtime(&t);
                ostringstream oss;
                oss << put_time(&tm, "%d-%m-%Y %H-%M-%S");
                auto str = oss.str();
                str= "Fecha: "+ str.substr(0,str.find(" "))+" Hora: "+ str.substr(str.find(" ")+1,str.size()-str.find(" "));
                string registar = str + " "+TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].GetNombreUsuario()+" "+tipo+" "+matricula+" "+ "Ingreso de vehiculo";
                //--------------------------------
            }
            else {

            }
        }
    }
    else {
        cout<<"La matricula que ha ingresado no se relaciona con el vehiculo. "<<endl;
    }
}
