#include "vehiculo.h"

vehiculo::vehiculo()
{

}

void vehiculo::SetBanderaParqueadero(int BanderaParqueaderoEntrante)
{
    BanderaParqueado=BanderaParqueaderoEntrante;
}

int vehiculo::GetBanderaParqueadero()
{
    return BanderaParqueado;
}

void vehiculo::SetCelda(int CeldaEntrante)
{
    celda=CeldaEntrante;
}

void vehiculo::SetPiso(int PisoEntrante)
{
    piso=PisoEntrante;
}

void vehiculo::SetTipoEstacionamiento(char TipoEntrante)
{
    Tparqueadero=TipoEntrante;
}

void vehiculo::SetPlacaVehiculo(string PlacaEntrante)
{
    placa=PlacaEntrante;
}

void vehiculo::SetTipoVehiculo(string TipoVehiculo)
{
    tipo=TipoVehiculo;
}

int vehiculo::GetCelda()
{
    return celda;
}

int vehiculo::GetPiso()
{
    return piso;
}

char vehiculo::GetTipoEstacionamiento()
{
    return Tparqueadero;
}

string vehiculo::GetPlacaVehiculo()
{
    return placa;
}

string vehiculo::GetTipoVehiculo()
{
    return tipo;
}

int vehiculo::GetTipoDeCobro()
{
    return TipoDeCobro;
}

void vehiculo::SetTipoDeCobro(int a)
{
    TipoDeCobro=a;
}
