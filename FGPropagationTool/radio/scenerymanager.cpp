#include "scenerymanager.h"
#include <QDebug>

SceneryManager::SceneryManager(DatabaseApi *db, FlightgearPrefs *settings)
{
    _srtmreader = new SRTMReader(db);
    _shpreader = new ShpReader(db);
    _settings = settings;
}

bool SceneryManager::get_elevation_m(const SGGeod &probe, double &elevation_m, string &material)
{

    _srtmreader->setCoordinates(probe.getLatitudeDeg(),probe.getLongitudeDeg());
    elevation_m = _srtmreader->readHeight();

    if(_settings->_use_clutter == 1)
    {
        _shpreader->setCoordinates(probe.getLatitudeDeg(),probe.getLongitudeDeg());
        QString mat = _shpreader->getTerrainType();
        material = mat.toStdString();
    }
    else
    {
        material = "None";
    }

    return true;
}
