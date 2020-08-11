#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "parqueadero.h"
#include <chrono>
#include <ctime>

using namespace std;

int main()
{
    parqueadero ParqueaderoNuevo;
     char OpcionMayor;
    do{
        OpcionMayor=ParqueaderoNuevo.MenoPricipal();
        if(OpcionMayor=='A'){
            string NombreUsuario;
            string contrasena;
            cout<<"Ingresa el nombre de usuario para el administrador: "<<endl;
            getline(cin,NombreUsuario);
            getline(cin,NombreUsuario);
            cout<<"Ingresa la contrasena: "<<endl;
            getline(cin,contrasena);
            if(ParqueaderoNuevo.VerificarInicioSesion(NombreUsuario,contrasena)==true){
                char OpcionMenor;
                do{
                    OpcionMenor=ParqueaderoNuevo.MenuInterfazAdministrador();
                    switch (OpcionMenor) {
                    case 'A' :
                    {
                        ParqueaderoNuevo.PorcentajeOcupadoDeCadaUnoDelosPisos();
                        break;
                    }
                    case 'B' :
                    {
                        int AuxSeleccionNivel;
                        do{
                            cout<<"Ingresa el nivel que deseas revisar: "<<endl;
                            cin>>AuxSeleccionNivel;
                            if(AuxSeleccionNivel<1 or AuxSeleccionNivel>5){
                                cout<<"Opcion invalida. "<<endl;
                            }
                        }while(AuxSeleccionNivel<1 or AuxSeleccionNivel>5);
                        ParqueaderoNuevo.RegistroDeVehiculosPorNivel(AuxSeleccionNivel);
                        break;
                    }
                    case 'C' :
                    {
                        ParqueaderoNuevo.VisualizarTarifas();
                        break;
                    }
                    case 'D' :
                    {
                        ParqueaderoNuevo.CambiarCrearTabladeTarifas();
                        break;
                    }
                    case 'E' :
                    {
                        int AuxSeleccionNivel;
                        do{
                            cout<<"Ingresa el nivel que deseas revisar: "<<endl;
                            cin>>AuxSeleccionNivel;
                            if(AuxSeleccionNivel<1 or AuxSeleccionNivel>5){
                                cout<<"Opcion invalida. "<<endl;
                            }
                        }while(AuxSeleccionNivel<1 or AuxSeleccionNivel>5);
                        if(AuxSeleccionNivel==1){
                            ParqueaderoNuevo.ReportePorNivelEnLoQueVaDelDia("nivel1.txt");

                        }
                        else if (AuxSeleccionNivel==2) {
                            ParqueaderoNuevo.ReportePorNivelEnLoQueVaDelDia("nivel2.txt");
                        }
                        else if(AuxSeleccionNivel==3){
                            ParqueaderoNuevo.ReportePorNivelEnLoQueVaDelDia("nivel3.txt");
                        }
                        else if (AuxSeleccionNivel==4) {
                            ParqueaderoNuevo.ReportePorNivelEnLoQueVaDelDia("nivel4.txt");
                        }
                        else {
                            ParqueaderoNuevo.ReportePorNivelEnLoQueVaDelDia("nivel5.txt");
                        }
                        break;
                    }
                    case 'F' :
                    {
                        ParqueaderoNuevo.ReporteTotalEnLoQueVaDelDia();
                        break;
                    }
                    case 'G':
                    {
                        cout<<"Gracias por confiar en nosostros. "<<endl;
                        break;
                    }
                    default:
                    {
                        cout<<"La opcion no se reconoce. "<<endl;
                        break;
                    }
                 }
                }while(OpcionMenor!= 'G');
            }
            else {
                cout<<"El usuairo o contrasea es incorrecto. "<<endl;
            }

        }
        else if (OpcionMayor=='B') {
            string NombreUsuario;
            string contrasena;
            cout<<"Ingresa el nombre de usuario: "<<endl;
            getline(cin,NombreUsuario);
            getline(cin,NombreUsuario);
            cout<<"Ingresa la contrasena: "<<endl;
            getline(cin,contrasena);

            if(ParqueaderoNuevo.BuscarUsuarioIngresado(NombreUsuario,contrasena)==true){
                char OpcionMenor;
                do{
                    OpcionMenor=ParqueaderoNuevo.MenuInterfazUsuario();
                    switch (OpcionMenor) {
                    case 'A' :
                    {
                        int AuxSeleccionTipo;
                        string Placa;
                        cout<<"1. Carro. "<<endl;
                        cout<<"2. Moto.  "<<endl;
                        cout<<"3. Bicicleta. "<<endl;
                        do{
                            cout<<"Ingresa el tipo del vehiculo: "<<endl;
                            cin>>AuxSeleccionTipo;
                            if(AuxSeleccionTipo<1 or AuxSeleccionTipo>3){
                                cout<<"Opcion invalida. "<<endl;
                            }
                        }while(AuxSeleccionTipo<1 or AuxSeleccionTipo>3);

                        cout<<"Ingrese la placa: "<<endl;
                        cin>>Placa;
                        if(AuxSeleccionTipo==1){
                            ParqueaderoNuevo.AgregarVehiculoAmiNombre("Carro",Placa);
                        }
                        else if (AuxSeleccionTipo==2) {
                            ParqueaderoNuevo.AgregarVehiculoAmiNombre("Moto",Placa);
                        }
                        else {
                            ParqueaderoNuevo.AgregarVehiculoAmiNombre("Bicicleta",Placa);
                        }
                        break;
                    }
                    case 'B' :
                    {
                        int AuxSeleccionNivel;
                        string Placa;
                        cout<<"1. Carro. "<<endl;
                        cout<<"2. Moto.  "<<endl;
                        cout<<"3. Bicicleta. "<<endl;
                        do{
                            cout<<"Ingresa el tipo del vehiculo: "<<endl;
                            cin>>AuxSeleccionNivel;
                            if(AuxSeleccionNivel<1 or AuxSeleccionNivel>3){
                                cout<<"Opcion invalida. "<<endl;
                            }
                        }while(AuxSeleccionNivel<1 or AuxSeleccionNivel>3);

                        cout<<"Ingrese la placa: "<<endl;
                        cin>>Placa;
                        if(AuxSeleccionNivel==1){
                            ParqueaderoNuevo.EliminarVehiculoAmiNombre("Carro",Placa);
                        }
                        else if (AuxSeleccionNivel==2) {
                            ParqueaderoNuevo.EliminarVehiculoAmiNombre("Moto",Placa);
                        }
                        else {
                            ParqueaderoNuevo.EliminarVehiculoAmiNombre("Bicicleta",Placa);
                        }
                        break;
                    }
                    case 'C' :
                    {
                        ParqueaderoNuevo.CambiarTipoDeEstacionamiento();
                        break;
                    }
                    case 'D' :
                    {
                        ParqueaderoNuevo.MisVehiculos();
                        break;
                    }
                    case 'E' :
                    {
                        ParqueaderoNuevo.VisualizarTarifas();
                        break;
                    }
                    case 'F' :
                    {
                        ParqueaderoNuevo.IngresarVehiculoAlParqueadero();
                        break;
                    }
                    case 'G' :
                    {
                        ParqueaderoNuevo.SacarVehiculoDelParqueadero();
                        break;
                    }
                    case 'H':
                    {
                        cout<<"Gracias por confiar en nosostros. "<<endl;
                        break;
                    }
                    default:
                    {
                        cout<<"La opcion seleccionada no se reconoce. "<<endl;
                        break;
                    }
                }

                }while(OpcionMenor!='H');
            }
            else {
                cout<<"El nombre de usuario o contrasena es  incorrrecto. "<<endl;
            }
         }
        else if (OpcionMayor=='C') {
            string NombreUsuario;
            string contrasena;
            cout<<"Ingresa el nombre de usuario con el que quieres quedar registrado en el sistema: "<<endl;
            getline(cin,NombreUsuario);
            getline(cin,NombreUsuario);
            cout<<"Ingresa la contrasena: "<<endl;
            getline(cin,contrasena);
            ParqueaderoNuevo.RegistrarNuevoUsuario(NombreUsuario,contrasena);
        }
        else {
            cout<<"Cambios Guardado exitosamente. "<<endl;
        }

    }while(OpcionMayor!='D');
    return 0;
}


