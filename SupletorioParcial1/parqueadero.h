#ifndef PARQUEADERO_H
#define PARQUEADERO_H
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "usuario.h"
#include "vehiculo.h"
#include <list>
#include <sstream>
#include <iomanip>

using namespace std;
class parqueadero
{
public:
    parqueadero();
    //Para usuario
    //_____________________________________________________________
    //-------------------------------------------------------------
    //Funciones secundarias. No se explican.
    bool BuscarUsuarioIngresado(string,string);
    char MenuInterfazUsuario();
    void RegistrarNuevoUsuario(string, string);
    bool VerificarNombreIngresadoEstaEnArreglo(string);
    void cambio_diniero(int *);
    void TiqueteParaUsuario(vehiculo* ,int);
    void MovimientoRegistrar(string,string);
    //-------------------------------------------------------------

    void AgregarVehiculoAmiNombre(string,string);
    void EliminarVehiculoAmiNombre(string,string);
    bool VerificarSiEsELmismoVehiculo(string,string);
    void MisVehiculos();
    void CambiarTipoDeEstacionamiento();
    void IngresarVehiculoAlParqueadero();
    void SacarVehiculoDelParqueadero();
    //_____________________________________________________________

    //Para Administrador
    //_____________________________________________________________
    //-------------------------------------------------------------
    // Funciones secundarias. No se explican.
    bool VerificarInicioSesion(string, string);
    char MenuInterfazAdministrador();
    void ArchivoAdministrador();
    //-------------------------------------------------------------
    void PorcentajeOcupadoDeCadaUnoDelosPisos();
    void RegistroDeVehiculosPorNivel(int);
    void CambiarCrearTabladeTarifas();
    void ReportePorNivelEnLoQueVaDelDia(string);
    void ReporteTotalEnLoQueVaDelDia();
    //_____________________________________________________________

    //Para ambos.
    //_____________________________________________________________
    char MenoPricipal();
    void LeerRegistroDeUsuarios();
    int StringANumero(string);
    void LlenarConUsuariosRegistrados(string);
    void LlenarMasDatosDelConductor();
    void AccederDatosConductor(string,int);
    void DescomponerInformacionUsuario(string,int);
    void VisualizarTarifas();
    bool SinpreciosTodavia();
    void LeerTarifas();
    void DescomponerInformacionTarifas(string);
    void RegistrarTarifa();
    void RegistrarUsuariosActuales();
    void RegistrarArchivoPorUsuario(string,int);
    void DesactivarCeldasOcupadas();
    //_____________________________________________________________
private:
    vector<usuario> TodosLosUsuarios; // Vector que contiene todos los usuarios registrados.
    string UsuarioAdmi,ContrasenaAdmni; // Usuario y contraseña del administrador. Desde el contstrucor se extrae.
    int PosicionUsuarioQueHaIniciadoSesion; // Guarde la posicion del usuario que haya iniciado sesion en el arreglo. Para acceder a el de manera rápida.
    map<string,vector<int>> TiposDeVehiculos; // Contiene las tarifas.
    int CeldasTotalesP12=70;           // Es el numero de celdas totales que hay en el piso 1 y 2. Corresponde a motos.
    int CeldasTotalesP345=50;          // Es el numero de celdas totales que hay en los pisos 1,2 y3.
    list<int> CeldasDisponiblesPiso1;  // Contiene las celdas disponibles que hay en el piso 1.
    list<int> CeldasDisponiblesPiso2;  // Contiene las celdas disponibles que hay en el piso 2.
    list<int> CeldasDisponiblesPiso3;  // Contiene las celdas disponibles que hay en el piso 3.
    list<int> CeldasDisponiblesPiso4;  // Contiene las celdas disponibles que hay en el piso 4.
    list<int> CeldasDisponiblesPiso5;  // Contiene las celdas disponibles que hay en el piso 5.

};

#endif // PARQUEADERO_H
