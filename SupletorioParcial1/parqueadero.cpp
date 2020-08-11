#include "parqueadero.h"
#include <math.h>
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
    ArchivoAdministrador();
    LeerTarifas();
    LeerRegistroDeUsuarios();
    LlenarMasDatosDelConductor();
    DesactivarCeldasOcupadas();
}

bool parqueadero::BuscarUsuarioIngresado(string NombreUsuario, string Contrasena)
{
    // Verifica si el usuario y contrasena que se ingreso es correcto.

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
        cout<<endl;
        cout<<endl;
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
        if(opcion != 'A' and opcion != 'B' and opcion != 'C' and opcion != 'D' and opcion != 'E' and opcion != 'F' and opcion != 'G' and opcion != 'H'){
            cout<<"Opcion No Valida. "<<endl;
        }
    }while(opcion != 'A' and opcion != 'B' and opcion != 'C' and opcion != 'D' and opcion != 'E' and opcion != 'F' and opcion != 'G' and opcion != 'H');
    return opcion;
}

void parqueadero::RegistrarNuevoUsuario(string NuevoNombre, string contrasenaNueva)
{
    // Recibe un nombre de usuario y contraseña. si el nombre de usuario no está se crea el usuario nuevo.
    if(VerificarNombreIngresadoEstaEnArreglo(NuevoNombre)==false){
        usuario Auxiliar;
        Auxiliar.SetNombreUsuario(NuevoNombre);
        Auxiliar.SetContrasena(contrasenaNueva);
        TodosLosUsuarios.push_back(Auxiliar);
        ofstream CrearArchivoUsuario(NuevoNombre+".txt");
        RegistrarUsuariosActuales();
        CrearArchivoUsuario.close();
        cout<<"El usuario se ha creado exitosamente. "<<endl;
    }
    else {
        cout<<"El nombre solicitado ya se encuentra en uso. "<<endl;
    }
}

void parqueadero::AgregarVehiculoAmiNombre(string Tipo, string PlacaNueva)
{
    // Recibe el tipo de vehiculo y la placa para el registro de un nuevo vehiculo.
    // Revisa si que el tipo de placa no esten ya registrados.
    // y entoces registra un nuevo vehiculo para el usuario que haya iniciado sesion.
    if(VerificarSiEsELmismoVehiculo(Tipo,PlacaNueva)==false){
        vehiculo Auxiliar;
        // Parametros iniciales para cualquier vehiculo una vez se crea.
        //--------------------------------------------------------------
        Auxiliar.SetTipoVehiculo(Tipo);
        Auxiliar.SetPlacaVehiculo(PlacaNueva);
        Auxiliar.SetTipoEstacionamiento('T');
        Auxiliar.SetCelda(0);
        Auxiliar.SetPiso(0);
        Auxiliar.SetBanderaParqueadero(0);
        Auxiliar.SetTipoDeCobro(0);
        Auxiliar.Ingreso.dia=0;
        Auxiliar.Ingreso.hora=0;
        Auxiliar.Ingreso.minutos=0;
        Auxiliar.Ingreso.segundos=0;
        //---------------------------------------------------------------
        TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].VehiculosRegistrados.push_back(Auxiliar);
        RegistrarArchivoPorUsuario(TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].GetNombreUsuario()+".txt",PosicionUsuarioQueHaIniciadoSesion);
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
    // Recibe el tipo de vehiculo y la placa del vehiculo que se va a elimnar de los vehiculos a nombre del usuario que ha iniciado sesion.
    if(VerificarSiEsELmismoVehiculo(Tipo,placa)==true){ // Verifica que el vehiculo sí esté dentro de los veiculos registrados.
        //Itera sobre los vehiculos del usuario.
        for (auto i = TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].VehiculosRegistrados.begin();i!=TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].VehiculosRegistrados.end(); i++) {
            if((*i).GetPlacaVehiculo()==placa and (*i).GetTipoVehiculo()==Tipo){
                //Una vez que el tipo de vehiculo y placa coincide se procede a eliminar.
                TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].VehiculosRegistrados.erase(i);
                i = TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].VehiculosRegistrados.begin();
            }
        }
        // Guarda los cambios.
        RegistrarArchivoPorUsuario(TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].GetNombreUsuario()+".txt",PosicionUsuarioQueHaIniciadoSesion);
        cout<<"Vehiculo eliminado exitosamente. "<<endl;
        char a;
        cout<<"Ingrese cualquier tecla para continuar: "<<endl;
        cin>>a;
    }
    else {
        cout<<"Lo sentimos pero no es posible elimnar de su registro un vehiculo que no esta registrado. "<<endl;
        cout<<"Vuelve a intentarlo. "<<endl;
    }
}

bool parqueadero::VerificarSiEsELmismoVehiculo(string Tipo, string PlacaNueva)
{
    // Dado el tipo y placa de un vehiculo. Verifica si este vehiculo existe dentro de los vehiculos del usuario.
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
    /* Esta funcion permite cambiar el tipo de estacionamiento de un vehiculo en particular.
     */

    // Se pregunta por el tipo y la placa del vehiculo que se va a cambiar.
    //------------------------------------------------------------------
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
    //------------------------------------------------------------------------
    if(VerificarSiEsELmismoVehiculo(tipo,placa)==true){ // Se verifica si en efecto ese vehiculo existe.
        list<vehiculo>::iterator i;
        // Se itera sobre los vehiculos del usuario para acceder a la direccion de memoria del vehiculo deseado.
        for ( i = TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].VehiculosRegistrados.begin();i!=TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].VehiculosRegistrados.end();i++) {
            if((*i).GetTipoVehiculo()==tipo and (*i).GetPlacaVehiculo()==placa){
                break;
            }
        }
        //------------------------------------------------------------------------------
        // Aqui se pide al usuario que seleccione el modo al cual va a pasar.
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
        //------------------------------------------------------------------------------
        if(modo=='M'){
            if((*i).GetTipoEstacionamiento()=='M'){ // Si el modo al cual va a pasar y el modo en el que está son los mismos.
                                                  // Es un error, por lo que no se va hacer nada a continuacion.S
                if(tipo=="Carro")
                    cout<<"El "<<tipo<<" con placa "<<placa<<" ya tenía este modo. "<<endl;
                else
                    cout<<"La "<<tipo<<" con placa "<<placa<<" ya tenía este modo. "<<endl;
            }
            else {
                // Esto se pregunta debido a que si un vehiculo que no tiene mensualidad no está dentro del parqueadero.
                // Este tiene el piso y la celda iguales a cero.

                if((*i).GetPiso()==0 or (*i).GetCelda()==0){
                    /* Si un vehiculo tiene mensualidad a este se le reservará una celda por todo el mes. Nadie mas
                     * la usuará independientemente si está en uso o no.
                     */
                    int PisoSeleccionar,escogercelda;
                    cout<<"Ahora tendra que seleccionar el nivel y la celda que quiero reservar por todo el mes. "<<endl;
                    cout<<"Esta sera de uso exclusivo suyo. Nadie mas la utilizara. "<<endl;
                    // De acuerdo al vehiculo que se deberá seleccionar el piso en el cual va a estar el vehiculo.
                    if(tipo=="Carro"){
                        // Se pregunta el piso.
                        //-----------------------------------------------------------
                        do{
                            cout<<"Por favor, ingrese el piso (3 o 4): "<<endl;
                            cin>>PisoSeleccionar;
                            if(PisoSeleccionar != 3 and PisoSeleccionar != 4)
                                cout<<"Piso invalido para el tipo de vehiculo. "<<endl;

                        }while(PisoSeleccionar != 3 and PisoSeleccionar != 4);
                        //--------------------------------------------------------------
                        if(PisoSeleccionar==3){
                            cout<<"Celdas disponibles: "<<endl; // Muestra las celdas disponibles del piso 3
                            for(int iterador:CeldasDisponiblesPiso3){
                                cout<<iterador<<" ";
                            }
                            cout<<endl;

                            // Aqui se le pide al usuario que ingrese la celda que desea el nivel 3.
                            // se busca entre las celdas disponibles y si se encuentra se procede a eliminar.
                            //------------------------------------------------------------------------
                            list <int>::iterator i2=CeldasDisponiblesPiso3.begin();
                            do{
                                cout<<"Ingrese la celda en la que desea  estacionarse: "<<endl;
                                cin>>escogercelda;
                                for(i2 = CeldasDisponiblesPiso3.begin(); i2!= CeldasDisponiblesPiso3.end();i2++){
                                    if((*i2)==escogercelda){
                                        break;
                                    }
                                }
                                if((*i2)!=escogercelda)
                                    cout<<"La celda ingresada no se encuentra disponibles. "<<endl;

                            }while((*i2)!=escogercelda);
                            CeldasDisponiblesPiso5.erase(i2);
                            //--------------------------------------------------------------------------
                        }
                        else {
                            cout<<"Celdas disponibles: "<<endl;// Celdas disponibles del piso 4.
                            for(int iterador:CeldasDisponiblesPiso4){
                                cout<<iterador<<" ";
                            }
                            cout<<endl;

                            // Aqui se le pide al usuario que ingrese la celda que desea el nivel 4
                            // se busca entre las celdas disponibles y si se encuentra se procede a eliminar.
                            //------------------------------------------------------------------------
                            list <int>::iterator i2=CeldasDisponiblesPiso4.begin();
                            do{
                                cout<<"Ingrese la celda en la que desea  estacionarse: "<<endl;
                                cin>>escogercelda;
                                for(i2 = CeldasDisponiblesPiso4.begin(); i2!= CeldasDisponiblesPiso4.end();i2++){
                                    if((*i2)==escogercelda){
                                        break;
                                    }
                                }
                                if((*i2)!=escogercelda)
                                    cout<<"La celda ingresada no se encuentra disponibles. "<<endl;

                            }while((*i2)!=escogercelda);
                            CeldasDisponiblesPiso4.erase(i2);
                            //--------------------------------------------------------------------------
                        }


                        // Se procede a guardar en el vehiculo el piso y la celda que se seleccionaron,
                        (*i).SetCelda(escogercelda);
                        (*i).SetPiso(PisoSeleccionar);

                    }
                    else if (tipo == "Moto") {
                        // Lo mismo que con el carro. Solo que ahora los pisos a considerar son el 1 y el 2.
                        do{
                            cout<<"Por favor, ingrese el piso (1 o 2): "<<endl;
                            cin>>PisoSeleccionar;
                            if(PisoSeleccionar != 1 and PisoSeleccionar != 2)
                                cout<<"Piso invalido para el tipo de vehiculo. "<<endl;

                        }while(PisoSeleccionar != 1 and PisoSeleccionar != 2);

                        if(PisoSeleccionar==1){
                            cout<<"Celdas disponibles: "<<endl;
                            for(int iterador:CeldasDisponiblesPiso1){
                                cout<<iterador<<" ";
                            }
                            cout<<endl;
                            list <int>::iterator i2=CeldasDisponiblesPiso1.begin();
                            do{
                                cout<<"Ingrese la celda en la que desea  estacionarse: "<<endl;
                                cin>>escogercelda;
                                for(i2 = CeldasDisponiblesPiso1.begin(); i2!= CeldasDisponiblesPiso1.end();i2++){
                                    if((*i2)==escogercelda){
                                        break;
                                    }
                                }
                                if((*i2)!=escogercelda)
                                    cout<<"La celda ingresada no se encuentra disponibles. "<<endl;

                            }while((*i2)!=escogercelda);
                            CeldasDisponiblesPiso1.erase(i2);
                        }
                        else {
                            cout<<"Celdas disponibles: "<<endl;
                            for(int iterador:CeldasDisponiblesPiso2){
                                cout<<iterador<<" ";
                            }
                            cout<<endl;
                            list <int>::iterator i2=CeldasDisponiblesPiso2.begin();
                            do{
                                cout<<"Ingrese la celda en la que desea  estacionarse: "<<endl;
                                cin>>escogercelda;
                                for(i2 = CeldasDisponiblesPiso2.begin(); i2!= CeldasDisponiblesPiso2.end();i2++){
                                    if((*i2)==escogercelda){
                                        break;
                                    }
                                }
                                if((*i2)!=escogercelda)
                                    cout<<"La celda ingresada no se encuentra disponibles. "<<endl;

                            }while((*i2)!=escogercelda);
                            CeldasDisponiblesPiso2.erase(i2);
                        }

                        (*i).SetCelda(escogercelda);
                        (*i).SetPiso(PisoSeleccionar);
                    }
                    else {

                    // En el caso de la cicla, solo hay un piso ha considerar.
                    PisoSeleccionar=5;
                    cout<<"Celdas disponibles: "<<endl;
                    for(int iterador:CeldasDisponiblesPiso5){
                        cout<<iterador<<" ";
                    }
                    cout<<endl;
                    list <int>::iterator i2=CeldasDisponiblesPiso5.begin();
                    do{
                        cout<<"Ingrese la celda en la que desea  estacionarse: "<<endl;
                        cin>>escogercelda;
                        for(i2 = CeldasDisponiblesPiso5.begin(); i2!= CeldasDisponiblesPiso5.end();i2++){
                            if((*i2)==escogercelda){
                                break;
                            }
                        }
                        if((*i2)!=escogercelda)
                            cout<<"La celda ingresada no se encuentra disponibles. "<<endl;

                    }while((*i2)!=escogercelda);
                     CeldasDisponiblesPiso5.erase(i2);
                    (*i).SetCelda(escogercelda);
                    (*i).SetPiso(PisoSeleccionar);
                    }
                }

                // Si un usuario pasa a mensualidad. Este deberá pagar desde el inicio.
                int dinero;
                cout<<"Como usted va a pasar al modo mensual necesita realizar el pago ya. "<<endl;
                cout<<"La cantidad de dinero a pagar es: "<<TiposDeVehiculos[tipo].at(2)<<endl;
                do{
                    cout<<"Ingrese la cantidad de dinero: "<<endl;
                    cin>>dinero;

                }while(dinero<TiposDeVehiculos[tipo].at(2));
                int cambio = dinero -TiposDeVehiculos[tipo].at(2);
                //------------------------------------------------------------------
                auto t = std::time(nullptr); // Obtiene la fecha y la hora para el registro por nivel.
                auto tm = *std::localtime(&t);
                ostringstream oss;
                oss << put_time(&tm, "%d-%m-%Y %H-%M-%S");
                auto str = oss.str();
                str= "Fecha: "+ str.substr(0,str.find(" "))+" Hora: "+ str.substr(str.find(" ")+1,str.size()-str.find(" "));
                string registar = str + " "+TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].GetNombreUsuario()+ " " + tipo+" "+ placa+ " " + (*i).GetTipoEstacionamiento()+" - > "+ modo+" "+"Ocupa piso: "+to_string((*i).GetPiso())+ " Ocupa celda: "+ to_string((*i).GetCelda()) +" " +"Pago con: " +to_string(dinero)+ " Cambio: " + to_string(cambio);
                 // Se pregunta cual es el nivel que se ha elijido.
                // Se hace el registro por nivel.
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
                (*i).SetTipoEstacionamiento('M'); // Se establece el nuevo tipo de estacionamiento.
                (*i).SetTipoDeCobro(3);

                // Se guarda los cambios en el arhcivo del usuario.
                RegistrarArchivoPorUsuario(TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].GetNombreUsuario()+".txt",PosicionUsuarioQueHaIniciadoSesion);
            }
        }
        else {
            if((*i).GetTipoEstacionamiento()=='T'){  // Si el modo al cual va a pasar y el modo en el que está son los mismos.
                                                    // Es un error.
                if(tipo=="Carro")
                    cout<<"El "<<tipo<<" con placa "<<placa<<" ya tenía este modo. "<<endl;
                else
                    cout<<"La "<<tipo<<" con placa "<<placa<<" ya tenía este modo. "<<endl;
            }
            else {

                auto t = std::time(nullptr); // Obtiene la fecha y la hora para hacer el registro por nivel.
                auto tm = *std::localtime(&t);
                ostringstream oss;
                oss << put_time(&tm, "%d-%m-%Y %H-%M-%S");
                auto str = oss.str();
                str= "Fecha: "+ str.substr(0,str.find(" "))+" Hora: "+ str.substr(str.find(" ")+1,str.size()-str.find(" "));
                /* Hay dos situaciones:
                 * 1. Que al momento del cambio el vehiculo se encuentre dentro del estacionamiento
                 * 2. Que no lo haga.
                 */
                if((*i).GetBanderaParqueadero()==1){
                    // Si el vehiculo se encuentra dentro del estacionamiento. Se le empezará a cobrar desde ese momento.
                    // Extrae el tiempo
                    time_t currentTime = time(NULL);
                    time(&currentTime);
                    struct tm *myTime = localtime(&currentTime);
                    //------------------------------------------
                    (*i).Ingreso.dia=myTime->tm_mday;  //Devuelve el día del mes.
                    (*i).Ingreso.hora=myTime->tm_hour;  //Devuelve la hora.
                    (*i).Ingreso.minutos=myTime->tm_min; // Devuelve los minutos.
                    (*i).Ingreso.segundos=myTime->tm_sec; // Devuelve los segundos.
                    //_______________________________
                    int TipoDeCobroAux;
                 do{
                    // Si se tiene un tipo de estacionamiento temporal.
                    // Se debe escoger si el cobro se lo harán por hora o por día.
                    cout<<"Ingrese la clase de cobro que se le hara: "<<endl;
                    cout<<"1. Quiero que me cobren por hora. "<<endl;
                    cout<<"2. Quiero que me cobren pir dias. "<<endl;
                    cout<<"Recuerda que si decides que el cobro se te haga por días. No podras sacar el mismo hasta que se cumpla al menos un dia. "<<endl;
                    cin>>TipoDeCobroAux;
                    if(TipoDeCobroAux != 1 and TipoDeCobroAux != 2){
                        cout<<"Solo hay dos opciones. "<<endl;
                    }
                }while(TipoDeCobroAux != 1 and TipoDeCobroAux != 2);

                (*i).SetTipoDeCobro(TipoDeCobroAux);

                }
                else {
                    // Si el vehiculo no está en el parquedero se procederá a devolver la celda.
                    if((*i).GetPiso()==1){
                        CeldasDisponiblesPiso1.push_back((*i).GetCelda()); // Pone la celda al final de la lista.
                        CeldasDisponiblesPiso1.sort(); // Ordena la lista.
                    }
                    else if ((*i).GetPiso()==2) {
                        CeldasDisponiblesPiso2.push_back((*i).GetCelda());
                        CeldasDisponiblesPiso2.sort();
                    }
                    else if ((*i).GetPiso()==3) {
                        CeldasDisponiblesPiso3.push_back((*i).GetCelda());
                        CeldasDisponiblesPiso3.sort();
                    }
                    else if ((*i).GetPiso()==4) {
                        CeldasDisponiblesPiso4.push_back((*i).GetCelda());
                        CeldasDisponiblesPiso4.sort();
                    }
                    else {
                        CeldasDisponiblesPiso5.push_back((*i).GetCelda());
                        CeldasDisponiblesPiso5.sort();
                    }
                }
                string registar = str + " "+TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].GetNombreUsuario()+ " " + tipo+" "+ placa+ " " + (*i).GetTipoEstacionamiento()+" - > "+ modo+" "+"Desocupa piso: "+to_string((*i).GetPiso())+ " Desocupa celda: "+ to_string((*i).GetCelda()) +" " +"Pago con: " +to_string(0)+ " Cambio: " + to_string(0);

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

                if((*i).GetBanderaParqueadero()==0){
                    (*i).SetPiso(0);
                    (*i).SetCelda(0);
                    (*i).SetTipoDeCobro(0);
                }
                (*i).SetTipoEstacionamiento('T');

                // Guarda los cambios.
                RegistrarArchivoPorUsuario(TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].GetNombreUsuario()+".txt",PosicionUsuarioQueHaIniciadoSesion);
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
    // Muestra los vehiculos que estan registrados en el archivo del usuario.
    if(TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].VehiculosRegistrados.size()==0){
        cout<<"Aun no tienes ningun vehiculo registrado a tu nombre. "<<endl;
        return;
    }
    cout<<"Tipo                Placa            Tipo de estacionamiento             Piso              Celda           Bandera Parqueadero.  "<<endl;
    for(auto i : TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].VehiculosRegistrados){
        cout<<i.GetTipoVehiculo();
        for (int iterador=1;iterador<=20 - i.GetTipoVehiculo().size();iterador++) {
            cout<<" ";
        }
        cout<<i.GetPlacaVehiculo()<<"                        "<<i.GetTipoEstacionamiento()<<"                       "<<i.GetPiso()<<"                 "<<i.GetCelda()<<"                      "<<i.GetBanderaParqueadero()<<endl;
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
        }
    }while(opcion != 'A' and opcion != 'B' and opcion != 'C' and opcion != 'D' and opcion != 'E' and opcion != 'F' and opcion != 'G');
    return opcion;
}

void parqueadero::ArchivoAdministrador()
{
    // Abre el archivo en el cual esta el usuario y contraseña del administrador.
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
    // Muestra que tan lleno se encuentra cada uno de los niveles.
    int Ocupados,aproximar;
    float PorcentajeOcupado;
    cout<<"Nivel        Celdas Ocupadas         Celdas Totales            Porcentaje Ocupado            Tipo Vehiculo.        "<<endl;
    Ocupados=CeldasTotalesP12-CeldasDisponiblesPiso1.size();
    PorcentajeOcupado=(Ocupados/CeldasTotalesP12)*100;
    aproximar=PorcentajeOcupado*100;
    PorcentajeOcupado=aproximar;
    PorcentajeOcupado/=100;
    cout<<"  1               "<<Ocupados<<"                      "<<CeldasTotalesP12<<"                           "<<PorcentajeOcupado<<"                         Moto          "<<endl;
    Ocupados=CeldasTotalesP12-CeldasDisponiblesPiso2.size();
    PorcentajeOcupado=(Ocupados/CeldasTotalesP12)*100;
    aproximar=PorcentajeOcupado*100;
    PorcentajeOcupado=aproximar;
    PorcentajeOcupado/=100;
    cout<<"  2               "<<Ocupados<<"                      "<<CeldasTotalesP12<<"                           "<<PorcentajeOcupado<<"                         Moto          "<<endl;
    Ocupados=CeldasTotalesP345-CeldasDisponiblesPiso3.size();
    PorcentajeOcupado=(Ocupados/CeldasTotalesP345)*100;
    aproximar=PorcentajeOcupado*100;
    PorcentajeOcupado=aproximar;
    PorcentajeOcupado/=100;
    cout<<"  3               "<<Ocupados<<"                      "<<CeldasTotalesP345<<"                           "<<PorcentajeOcupado<<"                         Carro          "<<endl;
    Ocupados=CeldasTotalesP345-CeldasDisponiblesPiso4.size();
    PorcentajeOcupado=(Ocupados/CeldasTotalesP345)*100;
    aproximar=PorcentajeOcupado*100;
    PorcentajeOcupado=aproximar;
    PorcentajeOcupado/=100;
    cout<<"  4               "<<Ocupados<<"                      "<<CeldasTotalesP345<<"                           "<<PorcentajeOcupado<<"                         Carro          "<<endl;
    Ocupados=CeldasTotalesP345-CeldasDisponiblesPiso5.size();
    PorcentajeOcupado=(Ocupados/CeldasTotalesP345)*100;
    aproximar=PorcentajeOcupado*100;
    PorcentajeOcupado=aproximar;
    PorcentajeOcupado/=100;
    cout<<"  5               "<<Ocupados<<"                      "<<CeldasTotalesP345<<"                           "<<PorcentajeOcupado<<"                         Bicicleta          "<<endl;
}

void parqueadero::RegistroDeVehiculosPorNivel(int NivelSelecccionado)
{
    // Muestra cuales son los vehiculos que en ese momento están en el nivel seleccionado.
    if(TodosLosUsuarios.size()==0){
        cout<<"Aun no hay usuarios registrados"<<endl;
        return;
    }
    // Itera sobre todos los usuarios y sobre los vehiculos de cada uno de estos.
    cout<<"Nivel: "<<NivelSelecccionado<<endl;
    cout<<"Celda                Placa             Hora de ingreso        Tipo de estacionamiento         "<<endl;
    for (auto Iterador1 : TodosLosUsuarios) {
        for(auto Iterador2:Iterador1.VehiculosRegistrados){
            if(Iterador2.GetPiso()==NivelSelecccionado and Iterador2.GetBanderaParqueadero()==1){
                cout<<Iterador2.GetCelda()<<"                   "<<Iterador2.GetPlacaVehiculo()<<"                 "<<Iterador2.Ingreso.hora<<":"<<Iterador2.Ingreso.minutos<<":"<<Iterador2.Ingreso.segundos<<"                  "<<Iterador2.GetTipoEstacionamiento()<<"      "<<endl;
            }
        }
    }
}

void parqueadero::CambiarCrearTabladeTarifas()
{
    // Modifica los valoes de las tarifas.
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
    RegistrarTarifa();

}

void parqueadero::ReportePorNivelEnLoQueVaDelDia(string NombreArchivo)
{
    // Esta funcion recibe el nombre del archivo que se va a querer revisar y se imprime su contenido.
    // Se imprime sin mas porque en el arhivo la informacion ya se encuentra organizada.

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
    // Muestra el reporte de todos los niveles.
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
    // Imprime la tarifa en pantalla.
    string auxilar;
    if(SinpreciosTodavia()==true){
        cout<<"TIPO              HORA                 DIA                MES      "<<endl;
        for(auto i : TiposDeVehiculos){
            cout<<i.first;
            auxilar=i.first;
            for (int i=1;i<=18-auxilar.size();i++) {
                cout<<" ";
            }
            cout<<i.second.at(0)<<"               "<<i.second.at(1)<<"               "<<i.second.at(2)<<endl;
        }
    }
    else {
        cout<<"Aun no hay una tarifa disponible. "<<endl;
    }
}

bool parqueadero::SinpreciosTodavia()
{
    // Verifica que la tarifa no esté en ceros.
    // Ya que esto significa que aun no se creado una tarifa.
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
    // Recibe el nombre del archivo (nombre de usuario + .txt) y la posicion en el arreglo de usuarios.
    // Actualiza la informacion del mismo.
    ofstream archivoUsuarios(usuario);

    if(archivoUsuarios.fail())
        cout<<"Error al abrir el archivo. LeerRegistroUsuairos"<<endl;
    else {
        for(auto i: TodosLosUsuarios[posicionActual].VehiculosRegistrados){
            archivoUsuarios<<i.GetTipoVehiculo()<<","<<i.GetPlacaVehiculo()<<","<<i.GetTipoEstacionamiento()<<","<<i.GetPiso()<<","<<i.GetCelda()<<","<<i.GetBanderaParqueadero()<<","<<i.GetTipoDeCobro()<<","<<i.Ingreso.dia<<","<<i.Ingreso.hora<<","<<i.Ingreso.minutos<<","<<i.Ingreso.segundos<<endl;
        }
    }

    archivoUsuarios.close();
}

void parqueadero::DesactivarCeldasOcupadas()
{
    /* Al inicio del programa todos las celdas estan disponibles. Pero eso es un error
     * Para solucionar esto se itera sobre todos los usuarios y a su vez sobre todos los vehiculos de esto verificando
     * cuales son las celdas que no estan disponibles. Y elimina de las celdas disponibles las que no lo estan.
     */
    for (auto Iterador1: TodosLosUsuarios) {
        for(auto Iterador2: Iterador1.VehiculosRegistrados){
            if(Iterador2.GetPiso()==1){
                for (auto IteradorLista1=CeldasDisponiblesPiso1.begin();IteradorLista1!=CeldasDisponiblesPiso1.end();IteradorLista1++) {
                    if(*IteradorLista1==Iterador2.GetCelda()){
                        CeldasDisponiblesPiso1.erase(IteradorLista1);
                        IteradorLista1=CeldasDisponiblesPiso1.begin();
                    }
                }
            }
            else if (Iterador2.GetPiso()==2) {
                for (auto IteradorLista2=CeldasDisponiblesPiso2.begin();IteradorLista2!=CeldasDisponiblesPiso2.end();IteradorLista2++) {
                    if(*IteradorLista2==Iterador2.GetCelda()){
                        CeldasDisponiblesPiso2.erase(IteradorLista2);
                        IteradorLista2=CeldasDisponiblesPiso2.begin();
                    }
                }
            }
            else if (Iterador2.GetPiso()==3) {
                for (auto IteradorLista3=CeldasDisponiblesPiso1.begin();IteradorLista3!=CeldasDisponiblesPiso3.end();IteradorLista3++) {
                    if(*IteradorLista3==Iterador2.GetCelda()){
                        CeldasDisponiblesPiso3.erase(IteradorLista3);
                        IteradorLista3=CeldasDisponiblesPiso3.begin();
                    }
                }
            }
            else if (Iterador2.GetPiso()==4) {
                for (auto IteradorLista4=CeldasDisponiblesPiso4.begin();IteradorLista4!=CeldasDisponiblesPiso4.end();IteradorLista4++) {
                    if(*IteradorLista4==Iterador2.GetCelda()){
                        CeldasDisponiblesPiso4.erase(IteradorLista4);
                        IteradorLista4=CeldasDisponiblesPiso4.begin();
                    }
                }
            }
            else if(Iterador2.GetPiso()==5) {
                for (auto IteradorLista5=CeldasDisponiblesPiso5.begin();IteradorLista5!=CeldasDisponiblesPiso5.end();IteradorLista5++) {
                    if(*IteradorLista5==Iterador2.GetCelda()){
                        CeldasDisponiblesPiso5.erase(IteradorLista5);
                        IteradorLista5=CeldasDisponiblesPiso5.begin();
                    }
                }
            }
        }
    }
}

void parqueadero::LlenarMasDatosDelConductor()
{
    // Actualiza la informacion de todos los archivos.
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
    int ExtraerDia=StringANumero(renglon.substr(0,PosicionComa));
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
    Auxiliar.SetCelda(ExtraerCelda);
    Auxiliar.SetTipoEstacionamiento(ExtraerTiempo[0]);
    Auxiliar.SetTipoVehiculo(ExtraerTipo);
    Auxiliar.SetPlacaVehiculo(ExtraerPlaca);
    Auxiliar.SetBanderaParqueadero(ExtraerBanderaParqueadero);
    Auxiliar.SetTipoDeCobro(ExtraerTipoDeCobro);
    Auxiliar.Ingreso.dia=ExtraerDia;
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
    // Registra en el archivo el movimiento.
    // Archivo-> Es el nombre del archivo que guarda la informacion de un determinado nivel.
    // movimiento-> Transaccion que se hizo (sacar o meter vehiculo en el parqueadero. Cambio de menbresia.
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
    if(TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].VehiculosRegistrados.size()==0){
        // Verifica si el usuario que inicio sesion tiene al menos un vehiculo registrado a su nombre.
        cout<<"Lo sentimos pero no es posible realizar esta accion si no tienes registrado ningun vehiculo a tu nombre. "<<endl;
        return;
    }
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
        // Se itera sobre los vehiculos del usuario que inició sesión para encontrar el vehiculo que se va a manipular.
        list<vehiculo>::iterator i;
        for ( i = TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].VehiculosRegistrados.begin();i!=TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].VehiculosRegistrados.end();i++) {
            if((*i).GetTipoVehiculo()==tipo and (*i).GetPlacaVehiculo()==matricula){
                // Se verifica si el auto no está dentro del parqueadero.
                break;
            }
        }
        if((*i).GetBanderaParqueadero()==1){
            cout<<"Lo sentimos pero el vehiculo ya se encuentra en el parqueadero. "<<endl;
        }
        else {
            int PisoSeleccionar;
            int  escogercelda;
            int tipoaux;
            if((*i).GetTipoEstacionamiento()=='T'){
                // Segun el tipo de heiculo que se ingrese, hay destinados unos determinados pisos del estacionamiento.
                if(tipo=="Carro"){
                    do{
                        cout<<"Por favor, ingrese el piso (3 o 4): "<<endl;
                        cin>>PisoSeleccionar;
                        if(PisoSeleccionar != 3 and PisoSeleccionar != 4)
                            cout<<"Piso invalido para el tipo de vehiculo. "<<endl;

                    }while(PisoSeleccionar != 3 and PisoSeleccionar != 4);

                    if(PisoSeleccionar==3){
                        // Muesta las celdas disponibles del piso seleccionado.
                        cout<<"Celdas disponibles: "<<endl;
                        for(int iterador:CeldasDisponiblesPiso3){
                            cout<<iterador<<" ";
                        }
                        cout<<endl;
                        list <int>::iterator i2=CeldasDisponiblesPiso3.begin();
                        do{
                            cout<<"Ingrese la celda en la que desea  estacionarse: "<<endl;
                            cin>>escogercelda;
                            for(i2 = CeldasDisponiblesPiso3.begin(); i2!= CeldasDisponiblesPiso3.end();i2++){
                                // Se itera sobre las celdas libres para verificar que se ha seleccionado una que esté libre.
                                if((*i2)==escogercelda){
                                    break;
                                }
                            }
                            if((*i2)!=escogercelda)
                                cout<<"La celda ingresada no se encuentra disponibles. "<<endl;

                        }while((*i2)!=escogercelda);
                        // Se elimina de las celdas libres la celda seleccionada.
                        CeldasDisponiblesPiso5.erase(i2);
                    }
                    else {
                        // Muesta las celdas disponibles del piso seleccionado.
                        cout<<"Celdas disponibles: "<<endl;
                        for(int iterador:CeldasDisponiblesPiso4){
                            cout<<iterador<<" ";
                        }
                        cout<<endl;
                        list <int>::iterator i2=CeldasDisponiblesPiso4.begin();
                        do{
                            cout<<"Ingrese la celda en la que desea  estacionarse: "<<endl;
                            cin>>escogercelda;
                            for(i2 = CeldasDisponiblesPiso4.begin(); i2!= CeldasDisponiblesPiso4.end();i2++){
                                // Se itera sobre las celdas del nivel seleccionado para verificar que se ha seleccionado
                                // una celda que está libre.
                                if((*i2)==escogercelda){
                                    break;
                                }
                            }
                            if((*i2)!=escogercelda)
                                cout<<"La celda ingresada no se encuentra disponibles. "<<endl;

                        }while((*i2)!=escogercelda);
                        // Se elimina de las celdas libres de ese nivel la celda seleccionada.
                        CeldasDisponiblesPiso4.erase(i2);
                    }

                    // Se altera la celda y el piso del vehiculo que se está tratando.
                    (*i).SetCelda(escogercelda);
                    (*i).SetPiso(PisoSeleccionar);

                }
                else if (tipo == "Moto") {
                    do{
                        cout<<"Por favor, ingrese el piso (1 o 2): "<<endl;
                        cin>>PisoSeleccionar;
                        if(PisoSeleccionar != 1 and PisoSeleccionar != 2)
                            cout<<"Piso invalido para el tipo de vehiculo. "<<endl;

                    }while(PisoSeleccionar != 1 and PisoSeleccionar != 2);

                    if(PisoSeleccionar==1){
                        cout<<"Celdas disponibles: "<<endl;
                        for(int iterador:CeldasDisponiblesPiso1){
                            cout<<iterador<<" ";
                        }
                        cout<<endl;
                        list <int>::iterator i2=CeldasDisponiblesPiso1.begin();
                        do{
                            cout<<"Ingrese la celda en la que desea  estacionarse: "<<endl;
                            cin>>escogercelda;
                            for(i2 = CeldasDisponiblesPiso1.begin(); i2!= CeldasDisponiblesPiso1.end();i2++){
                                if((*i2)==escogercelda){
                                    break;
                                }
                            }
                            if((*i2)!=escogercelda)
                                cout<<"La celda ingresada no se encuentra disponibles. "<<endl;

                        }while((*i2)!=escogercelda);
                        CeldasDisponiblesPiso1.erase(i2);
                    }
                    else {
                        cout<<"Celdas disponibles: "<<endl;
                        for(int iterador:CeldasDisponiblesPiso2){
                            cout<<iterador<<" ";
                        }
                        cout<<endl;
                        list <int>::iterator i2=CeldasDisponiblesPiso2.begin();
                        do{
                            cout<<"Ingrese la celda en la que desea  estacionarse: "<<endl;
                            cin>>escogercelda;
                            for(i2 = CeldasDisponiblesPiso2.begin(); i2!= CeldasDisponiblesPiso2.end();i2++){
                                if((*i2)==escogercelda){
                                    break;
                                }
                            }
                            if((*i2)!=escogercelda)
                                cout<<"La celda ingresada no se encuentra disponibles. "<<endl;

                        }while((*i2)!=escogercelda);
                        CeldasDisponiblesPiso2.erase(i2);
                    }

                    (*i).SetCelda(escogercelda);
                    (*i).SetPiso(PisoSeleccionar);
                }
                else {
                PisoSeleccionar=5;
                cout<<"Celdas disponibles: "<<endl;
                for(int iterador:CeldasDisponiblesPiso5){
                    cout<<iterador<<" ";
                }
                cout<<endl;
                list <int>::iterator i2=CeldasDisponiblesPiso5.begin();
                do{
                    cout<<"Ingrese la celda en la que desea  estacionarse: "<<endl;
                    cin>>escogercelda;
                    for(i2 = CeldasDisponiblesPiso5.begin(); i2!= CeldasDisponiblesPiso5.end();i2++){
                        if((*i2)==escogercelda){
                            break;
                        }
                    }
                    if((*i2)!=escogercelda)
                        cout<<"La celda ingresada no se encuentra disponibles. "<<endl;

                }while((*i2)!=escogercelda);
                 CeldasDisponiblesPiso5.erase(i2);
                (*i).SetCelda(escogercelda);
                (*i).SetPiso(PisoSeleccionar);
                }

                do{
                    // Si se tiene un tipo de estacionamiento temporal.
                    // Se debe escoger si el cobro se lo harán por hora o por día.
                    cout<<"Ingrese la clase de cobro que se le hara: "<<endl;
                    cout<<"1. Quiero que me cobren por hora. "<<endl;
                    cout<<"2. Quiero que me cobren pir dias. "<<endl;
                    cout<<"Recuerda que si decides que el cobro se te haga por días. No podras sacar el mismo hasta que se cumpla al menos un dia. "<<endl;
                    cin>>tipoaux;
                    if(tipoaux != 1 and tipoaux != 2){
                        cout<<"Solo hay dos opciones. "<<endl;
                    }
                }while(tipoaux != 1 and tipoaux != 2);

                (*i).SetTipoDeCobro(tipoaux);
                (*i).SetBanderaParqueadero(1);
                //------------------------------------------
                // Extrae el tiempo
                time_t currentTime = time(NULL);
                time(&currentTime);
                struct tm *myTime = localtime(&currentTime);
                //------------------------------------------
                (*i).Ingreso.dia=myTime->tm_mday;  //Devuelve el día del mes.
                (*i).Ingreso.hora=myTime->tm_hour;  //Devuelve la hora.
                (*i).Ingreso.minutos=myTime->tm_min; // Devuelve los minutos.
                (*i).Ingreso.segundos=myTime->tm_sec; // Devuelve los segundos.

                //_______________________________
                auto t = std::time(nullptr); // Obtiene la fecha y hora para el registro.
                auto tm = *std::localtime(&t);
                ostringstream oss;
                oss << put_time(&tm, "%d-%m-%Y %H-%M-%S");
                auto str = oss.str();
                str= "Fecha: "+ str.substr(0,str.find(" "))+" Hora: "+ str.substr(str.find(" ")+1,str.size()-str.find(" "));
                string registar = str + " "+TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].GetNombreUsuario()+" "+tipo+" "+matricula+" "+ "Ingreso de vehiculo Piso: " + to_string((*i).GetPiso())+" Celda: "+ to_string((*i).GetCelda());
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
                //--------------------------------
                // Registra en el archivo del usuario los cambios realizados a los vehiculos del mismo .
                RegistrarArchivoPorUsuario(TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].GetNombreUsuario()+".txt", PosicionUsuarioQueHaIniciadoSesion);
                cout<<"El ingreso al parquedaero se realizo con exito."<<endl;
            }
            else {
                (*i).SetBanderaParqueadero(1);
                // Extrae el tiempo
                time_t currentTime = time(NULL);
                time(&currentTime);
                struct tm *myTime = localtime(&currentTime);
                //------------------------------------------
                (*i).Ingreso.dia=myTime->tm_mday;  //Devuelve el día del mes.
                (*i).Ingreso.hora=myTime->tm_hour;  //Devuelve la hora.
                (*i).Ingreso.minutos=myTime->tm_min; // Devuelve los minutos.
                (*i).Ingreso.segundos=myTime->tm_sec; // Devuelve los segundos.
                //_______________________________
                auto t = std::time(nullptr); // Obtiene la fecha y hora para el registro.
                auto tm = *std::localtime(&t);
                ostringstream oss;
                oss << put_time(&tm, "%d-%m-%Y %H-%M-%S");
                auto str = oss.str();
                str= "Fecha: "+ str.substr(0,str.find(" "))+" Hora: "+ str.substr(str.find(" ")+1,str.size()-str.find(" "));
                string registar = str + " "+TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].GetNombreUsuario()+" "+tipo+" "+matricula+" "+ "Ingreso de vehiculo Piso: " + to_string((*i).GetPiso())+" Celda: "+ to_string((*i).GetCelda())+" "+(*i).GetTipoEstacionamiento();
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
                RegistrarArchivoPorUsuario(TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].GetNombreUsuario()+".txt", PosicionUsuarioQueHaIniciadoSesion);
                cout<<"El ingreso al parquedaero se realizo con exito."<<endl;
            }
        }
    }
    else {
        cout<<"La matricula que ha ingresado no se relaciona con el vehiculo. "<<endl;
    }
}

void parqueadero::SacarVehiculoDelParqueadero()
{
    if(TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].VehiculosRegistrados.size()==0){
        cout<<"Lo sentimos pero no es posible realizar esta accion si no tienes registrado ningun vehiculo a tu nombre. "<<endl;
        return;
    }
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

        if((*i).GetBanderaParqueadero()==0){
            cout<<"Lo sentimos, pero no es posible retirar un vehiculo que no se encuentra en el parqueadero. "<<endl;
        }
        else {
            string AutenticarContrasena;
            cout<<"Necesitamos que verifique sus datos. Ingrese su contrasena: "<<endl;
            cin>>AutenticarContrasena;
            if(AutenticarContrasena != TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].GetContasena()){
                cout<<"Su contrsena es incorrecta. "<<endl;
                return;
            }
            if((*i).GetTipoEstacionamiento()=='T'){
                int DiferenciaTiempo;
                int DineroPagar;
                // Extrae el tiempo
                time_t currentTime = time(NULL);
                time(&currentTime);
                struct tm *myTime = localtime(&currentTime);
                //------------------------------------------
                (*i).Salida.dia=myTime->tm_mday;  //Devuelve el día del mes.
                (*i).Salida.hora=myTime->tm_hour;  //Devuelve la hora.
                (*i).Salida.minutos=myTime->tm_min; // Devuelve los minutos.
                (*i).Salida.segundos=myTime->tm_sec; // Devuelve los segundos.

                if((*i).GetTipoDeCobro()==1){
                    DiferenciaTiempo= (*i).Salida.hora - (*i).Ingreso.hora;
                    if(abs((*i).Salida.minutos - (*i).Ingreso.minutos)< 15){
                        DiferenciaTiempo+=1;
                    }
                    DineroPagar=TiposDeVehiculos[tipo].at((*i).GetTipoDeCobro()-1)*DiferenciaTiempo;
                    int dinero;
                    TiqueteParaUsuario(&(*i),DineroPagar);
                    do{
                        cout<<"Ingrese la cantidad de dinero: "<<endl;
                        cin>>dinero;
                        if(dinero<DineroPagar)
                            cout<<"La cantidad de dinero ingresada es insuficiente. "<<endl;
                    }while(dinero< DineroPagar);
                     int cambio = dinero -DineroPagar;
                     //________________________________________________________________________
                     auto t = std::time(nullptr); // Obtiene la fecha y hora para el registro.
                     auto tm = *std::localtime(&t);
                     ostringstream oss;
                     oss << put_time(&tm, "%d-%m-%Y %H-%M-%S");
                     auto str = oss.str();
                     str= "Fecha: "+ str.substr(0,str.find(" "))+" Hora: "+ str.substr(str.find(" ")+1,str.size()-str.find(" "));
                     string registar = str + " "+TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].GetNombreUsuario()+" "+tipo+" "+matricula+" "+ "Salida de vehiculo Piso: " + to_string((*i).GetPiso())+" Celda: "+ to_string((*i).GetCelda())+" "+(*i).GetTipoEstacionamiento()+" Total: "+ to_string( DineroPagar) + " Cambio: "+to_string( cambio);
                     if((*i).GetPiso()==1){
                         CeldasDisponiblesPiso1.push_back((*i).GetCelda());
                         CeldasDisponiblesPiso1.sort();
                         MovimientoRegistrar("nivel1.txt",registar);
                     }
                     else if ((*i).GetPiso()==2) {
                         CeldasDisponiblesPiso2.push_back((*i).GetCelda());
                         CeldasDisponiblesPiso2.sort();
                         MovimientoRegistrar("nivel2.txt",registar);
                     }
                     else if ((*i).GetPiso()==3) {
                         CeldasDisponiblesPiso3.push_back((*i).GetCelda());
                         CeldasDisponiblesPiso3.sort();
                         MovimientoRegistrar("nivel3.txt",registar);
                     }
                     else if ((*i).GetPiso()==4) {
                         CeldasDisponiblesPiso4.push_back((*i).GetCelda());
                         CeldasDisponiblesPiso4.sort();
                         MovimientoRegistrar("nivel4.txt",registar);
                     }
                     else {
                         CeldasDisponiblesPiso5.push_back((*i).GetCelda());
                         CeldasDisponiblesPiso5.sort();
                         MovimientoRegistrar("nivel5.txt",registar);
                     }
                     //_____________________________________________________________________________________________
                     cout<<endl;
                     cout<<"Su cambio es: "<<endl;
                     cambio_diniero(&cambio);
                     cout<<"Con un resto de: "<<cambio<<endl;
                     (*i).Ingreso.dia=0;
                     (*i).Ingreso.hora=0;
                     (*i).Ingreso.minutos=0;
                     (*i).Ingreso.segundos=0;
                     (*i).SetPiso(0);
                     (*i).SetCelda(0);
                     (*i).SetBanderaParqueadero(0);
                     (*i).SetTipoDeCobro(0);
                     RegistrarArchivoPorUsuario(TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].GetNombreUsuario()+".txt",PosicionUsuarioQueHaIniciadoSesion);

                }

                else {
                    // Hacer modificaciones para que el programa permita cobrar por horas.
                    DiferenciaTiempo= (*i).Salida.dia - (*i).Ingreso.dia;
                    if(abs((*i).Salida.hora - (*i).Ingreso.hora) <5){
                        DiferenciaTiempo+=1;
                    }
                    DineroPagar=0;
                    TiqueteParaUsuario(&(*i),DineroPagar);
                    auto t = std::time(nullptr); // Obtiene la fecha y hora para el registro.
                    auto tm = *std::localtime(&t);
                    ostringstream oss;
                    oss << put_time(&tm, "%d-%m-%Y %H-%M-%S");
                    auto str = oss.str();
                    str= "Fecha: "+ str.substr(0,str.find(" "))+" Hora: "+ str.substr(str.find(" ")+1,str.size()-str.find(" "));
                    string registar = str + " "+TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].GetNombreUsuario()+" "+tipo+" "+matricula+" "+ "Salida de vehiculo" + to_string((*i).GetPiso())+" "+ to_string((*i).GetCelda())+" "+(*i).GetTipoEstacionamiento()+" "+ to_string( 0) + " "+to_string( 0);

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
                    (*i).Ingreso.dia=0;
                    (*i).Ingreso.hora=0;
                    (*i).Ingreso.minutos=0;
                    (*i).Ingreso.segundos=0;
                    (*i).SetBanderaParqueadero(0);
                    (*i).SetTipoDeCobro(0);
                    RegistrarArchivoPorUsuario(TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].GetNombreUsuario()+".txt",PosicionUsuarioQueHaIniciadoSesion);

                }
            }
            else
            {
                string AutenticarContrasena;
                cout<<"Necesitamos que verifique dus datos. Ingrese su contrasena: "<<endl;
                cin>>AutenticarContrasena;
                if(AutenticarContrasena != TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].GetContasena()){
                    cout<<"Su contrsena es incorrecta. "<<endl;
                    return;
                }
                (*i).SetBanderaParqueadero(0);
                auto t = std::time(nullptr); // Obtiene la fecha y hora para el registro.
                auto tm = *std::localtime(&t);
                ostringstream oss;
                oss << put_time(&tm, "%d-%m-%Y %H-%M-%S");
                auto str = oss.str();
                str= "Fecha: "+ str.substr(0,str.find(" "))+" Hora: "+ str.substr(str.find(" ")+1,str.size()-str.find(" "));
                string registar = str + " "+TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].GetNombreUsuario()+" "+tipo+" "+matricula+" "+ "Salida de vehiculo Piso: "+ to_string((*i).GetPiso())+" Celda: "+ to_string((*i).GetCelda())+" "+(*i).GetTipoEstacionamiento();
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
                RegistrarArchivoPorUsuario(TodosLosUsuarios[PosicionUsuarioQueHaIniciadoSesion].GetNombreUsuario()+".txt",PosicionUsuarioQueHaIniciadoSesion);
            }
        }

    }
    else {
        cout<<"La matricula ingresada no se relaciona con el vehiculo. "<<endl;
    }
}

void parqueadero::TiqueteParaUsuario(vehiculo * VehiculoManipulado, int TotalPagar)
{
    cout<<"=============================="<<endl;
    cout<<"|------- PARQUEADERO --------|"<<endl;
    cout<<"=============================="<<endl;
    cout<<"|------- HORA INGRESO -------|"<<endl;
    cout<<"|-------              -------|"<<endl;
    cout<<"|-------   "<<VehiculoManipulado->Ingreso.hora<<":"<<VehiculoManipulado->Ingreso.minutos<<":"<<VehiculoManipulado->Ingreso.segundos<<"   -------|"<<endl;
    cout<<"|-------              -------|"<<endl;
    cout<<"|-------  HORA SALIDA -------|"<<endl;
    cout<<"|-------              -------|"<<endl;
    cout<<"|-------   "<<VehiculoManipulado->Salida.hora<<":"<<VehiculoManipulado->Salida.minutos<<":"<<VehiculoManipulado->Salida.segundos<<"   -------|"<<endl;
    cout<<"|-------              -------|"<<endl;
    cout<<"|------- VALOR A PAGAR ------|"<<endl;
    cout<<"|-------              -------|"<<endl;
    cout<<"|-------    "<<TotalPagar<<"     -------|"<<endl;
    cout<<"|-------              -------|"<<endl;
    cout<<"|-------              -------|"<<endl;
    cout<<"|-------       "<<VehiculoManipulado->GetTipoEstacionamiento()<<"       -------|"<<endl;
    cout<<"|-------              -------|"<<endl;
    cout<<"|------- GRACIAS POR  -------|"<<endl;
    cout<<"|-------  SU VISITA   -------|"<<endl;
    cout<<"|-------              -------|"<<endl;
    cout<<"=============================="<<endl;
    cout<<endl;
    char r;
    cout<<"Ingrese cualquier letra para continuar: "<<endl;
    cin>>r;
}

bool parqueadero::VerificarInicioSesion(string Nentrante, string Centrante)
{
    // Verifica si el Usuario y contraseña ingresado son los del administrador.
    if(Nentrante==UsuarioAdmi and Centrante==ContrasenaAdmni)
        return true;

    return false;
}

