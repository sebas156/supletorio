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
    bool BuscarUsuarioIngresado(string,string);
    char MenuInterfazUsuario();
    bool RegistrarNuevoUsuario(string, string);
    void AgregarVehiculoAmiNombre(string,string);
    void EliminarVehiculoAmiNombre(string,string);
    bool VerificarSiEsELmismoVehiculo(string,string);
    bool VerificarNombreIngresadoEstaEnArreglo(string);
    void CambiarTipoDeEstacionamiento();
    void MisVehiculos();
    void cambio_diniero(int *);
    void MovimientoRegistrar(string,string);
    void IngresarVehiculoAlParqueadero();
    //_____________________________________________________________

    //Para Administrador
    //_____________________________________________________________
    char MenuInterfazAdministrador();
    void ArchivoAdministrador();
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
    vector<usuario> TodosLosUsuarios;
    string UsuarioAdmi,ContrasenaAdmni;
    int PosicionUsuarioQueHaIniciadoSesion;
    map<string,vector<int>> TiposDeVehiculos;
    int CeldasTotalesP12=70;
    int CeldasTotalesP345=50;
    list<int> CeldasDisponiblesPiso1;
    list<int> CeldasDisponiblesPiso2;
    list<int> CeldasDisponiblesPiso3;
    list<int> CeldasDisponiblesPiso4;
    list<int> CeldasDisponiblesPiso5;

};

#endif // PARQUEADERO_H
