#include "CohortInputer.h"

CohortInputer::CohortInputer() {
};

CohortInputer::~CohortInputer() {
};

void CohortInputer::setModelData(ModelData *mdp) {
  md = mdp;
}

int CohortInputer::init() {
  int error = 0;
  error = initChtidFile();
  error = initChtinitFile();
  error = initClmFile();
  error = initVegFile();
  error = initFireFile();
  return error;
};

int CohortInputer::initChtidFile() {
  chtidfname = md->chtinputdir +"cohortid.nc";
  NcError err(NcError::silent_nonfatal);
  NcFile chtidFile(chtidfname.c_str(), NcFile::ReadOnly);

  if(!chtidFile.is_valid()) {
    string msg = chtidfname+" is not valid";
    cout<<msg+"\n";
    return -1;
  }

  NcDim* chtD = chtidFile.get_dim("CHTID");

  if(!chtD->is_valid()) {
    string msg = "CHTD Dimension is no Valid in ChtidFile";
    cout<<msg+"\n";
    return -1;
  }

  md->act_chtno = chtD->size();
  return 0;
};

int CohortInputer::initChtinitFile() {
  if (!md->runeq) {  // 'runeq' doesn't require initial file
    chtinitfname = md->initialfile;
    NcError err(NcError::silent_nonfatal);
    NcFile chtinitFile(chtinitfname.c_str(), NcFile::ReadOnly);

    if(!chtinitFile.is_valid()) {
      string msg = chtinitfname+" is not valid";
      cout<<msg+"\n";
      return -1;
    }

    NcDim* chtD = chtinitFile.get_dim("CHTID");

    if(!chtD->is_valid()) {
      string msg = "CHTD Dimension is no Valid in file:" + chtinitfname;
      cout<<msg+"\n";
      return -1;
    }

    md->act_initchtno = chtD->size();
    return 0;
  }

  return -1;
};

int CohortInputer::initClmFile() {
  //netcdf error
  NcError err(NcError::silent_nonfatal);
  clmfname = md->chtinputdir+"climate.nc";
  NcFile clmncFile(clmfname.c_str(), NcFile::ReadOnly);

  if(!clmncFile.is_valid()) {
    string msg = clmfname+" is not valid";
    cout<<msg+"\n";
    return -1;
  }

  NcDim* clmD = clmncFile.get_dim("CLMID");

  if(!clmD->is_valid()) {
    string msg = "CLMID Dimension is not valid in 'climate.nc' !";
    cout<<msg+"\n";
    return -1;
  }

  md->act_clmno = clmD->size();  //actual atm data record number
  NcVar* clmyrV = clmncFile.get_var("YEAR");

  if(clmyrV==NULL) {
    string msg = "Cannot get YEAR in 'climate.nc' file! ";
    cout<<msg+"\n";
    return -1;
  } else {
    int yrno = 0;
    int yr = -1;
    clmyrV->set_cur(yrno);
    clmyrV->get(&yr, 1);
    md->act_clmyr_beg = yr;
    yrno = clmyrV->num_vals()-1;
    clmyrV->set_cur(yrno);
    clmyrV->get(&yr, 1);
    md->act_clmyr_end = yr;
    md->act_clmyr = yr - md->act_clmyr_beg + 1;  //actual atm data years
  }

  NcDim* monD = clmncFile.get_dim("MONTH");

  if(!monD->is_valid()) {
    string msg = "MONTH Dimension is not valid in 'climate.nc' !";
    cout<<msg+"\n";
    return -1;
  }

  return 0;
}

int CohortInputer::initVegFile() {
  vegfname = md->chtinputdir+"vegetation.nc";
  NcError err(NcError::silent_nonfatal);
  NcFile vegncFile(vegfname.c_str(), NcFile::ReadOnly);

  if(!vegncFile.is_valid()) {
    string msg = vegfname+" is not valid";
    cout<<msg+"\n";
    return -1;
  }

  NcDim* vegD = vegncFile.get_dim("VEGID");

  if(!vegD->is_valid()) {
    string msg = "VEGID Dimension is not valid in 'Vegtation.nc'!";
    cout<<msg+"\n";
    return -1;
  }

  md->act_vegno = vegD->size();  //actual vegetation data record number
  NcDim* vegsetD = vegncFile.get_dim("VEGSET");

  if(!vegsetD->is_valid()) {
    string msg = "VEGSET Dimension is not valid in 'Vegtation.nc'!";
    cout<<msg+"\n";
    return -1;
  }

  md->act_vegset = vegsetD->size();  //actual vegetation data sets
  return 0;
};

int CohortInputer::initFireFile() {
  firefname = md->chtinputdir + "fire.nc";
  NcError err(NcError::silent_nonfatal);
  NcFile firencFile(firefname.c_str(), NcFile::ReadOnly);

  if(!firencFile.is_valid()) {
    string msg = firefname+" is not valid";
    cout<<msg+"\n";
    return -1;
  }

  NcDim* fireD = firencFile.get_dim("FIREID");

  if(!fireD->is_valid()) {
    string msg = "FIREID Dimension is not valid in 'fire.nc'!";
    cout<<msg+"\n";
    return -1;
  }

  md->act_fireno = fireD->size();  //actual fire data record number
  NcDim* fireyrD = firencFile.get_dim("FIRESET");

  if(!fireyrD->is_valid()) {
    string msg = "FIRESET Dimension is not valid in 'fire.nc'! ";
    cout<<msg+"\n";
    return -1;
  }

  md->act_fireset=fireyrD->size();  //actual fire year-set number
  return 0;
};

// the following is for a input file containing data ids for each cohort
int CohortInputer::getChtDataids(int &chtid, int & initchtid, int & grdid,
                                 int & clmid,  int & vegid, int & fireid,
                                 const int &recno) {
  NcError err(NcError::silent_nonfatal);
  NcFile chtidFile(chtidfname.c_str(), NcFile::ReadOnly);
  NcVar* chtidV = chtidFile.get_var("CHTID");

  if(chtidV==NULL) {
    string msg = "Cannot get CHTID in 'cohortid.nc' file! ";
    cout<<msg+"\n";
    return -1;
  }

  chtidV->set_cur(recno);
  chtidV->get(&chtid, 1);
  NcVar* initchtidV = chtidFile.get_var("INITCHTID");

  if(initchtidV==NULL) {
    string msg = "Cannot get INITCHTID in 'cohortid.nc' file! ";
    cout<<msg+"\n";
    return -1;
  }

  initchtidV->set_cur(recno);
  initchtidV->get(&initchtid, 1);
  NcVar* grdidV = chtidFile.get_var("GRIDID");

  if(grdidV==NULL) {
    string msg = "Cannot get GRIDID in 'cohortid.nc' file! ";
    cout<<msg+"\n";
    return -1;
  }

  grdidV->set_cur(recno);
  grdidV->get(&grdid, 1);
  NcVar* clmidV = chtidFile.get_var("CLMID");

  if(clmidV==NULL) {
    string msg = "Cannot get CLMID in 'cohortid.nc' file! ";
    cout<<msg+"\n";
    return -1;
  }

  clmidV->set_cur(recno);
  clmidV->get(&clmid, 1);
  NcVar* vegidV = chtidFile.get_var("VEGID");

  if(vegidV==NULL) {
    string msg = "Cannot get VEGID in 'cohortid.nc' file! ";
    cout<<msg+"\n";
    return -1;
  }

  vegidV->set_cur(recno);
  vegidV->get(&vegid, 1);
  NcVar* fireidV = chtidFile.get_var("FIREID");

  if(fireidV==NULL) {
    string msg = "Cannot get FIREID in 'cohortid.nc' file! ";
    cout<<msg+"\n";
    return -1;
  }

  fireidV->set_cur(recno);
  fireidV->get(&fireid, 1);
  return 0;
};

// the following are for data Ids from input data files
int CohortInputer::getInitchtId(int &initchtid, const int &recno) {
  NcError err(NcError::silent_nonfatal);
  NcFile initFile(chtinitfname.c_str(), NcFile::ReadOnly);
  NcVar* initchtidV = initFile.get_var("CHTID");

  if(initchtidV==NULL) {
    string msg = "Cannot get CHTID in the initial file! ";
    cout<<msg+"\n";
    return -1;
  }

  initchtidV->set_cur(recno);
  initchtidV->get(&initchtid, 1);
  return 0;
};

int CohortInputer::getClmId(int &clmid, const int &recno) {
  NcError err(NcError::silent_nonfatal);
  NcFile clmFile(clmfname.c_str(), NcFile::ReadOnly);
  NcVar* clmidV = clmFile.get_var("CLMID");

  if(clmidV==NULL) {
    string msg = "Cannot get CLMID in 'climate.nc' file! ";
    cout<<msg+"\n";
    return -1;
  }

  clmidV->set_cur(recno);
  clmidV->get(&clmid, 1);
  return 0;
};

int CohortInputer::getVegId(int &vegid, const int &recno) {
  NcError err(NcError::silent_nonfatal);
  NcFile vegFile(vegfname.c_str(), NcFile::ReadOnly);
  NcVar* vegidV = vegFile.get_var("VEGID");

  if(vegidV==NULL) {
    string msg = "Cannot get VEGID in 'vegetation.nc' file! ";
    cout<<msg+"\n";
    return -1;
  }

  vegidV->set_cur(recno);
  vegidV->get(&vegid, 1);
  return 0;
};

int CohortInputer::getFireId(int &fireid, const int &recno) {
  NcError err(NcError::silent_nonfatal);
  NcFile fireFile(firefname.c_str(), NcFile::ReadOnly);
  NcVar* fireidV = fireFile.get_var("FIREID");

  if(fireidV==NULL) {
    string msg = "Cannot get FIREID in 'fire.nc' file! ";
    cout<<msg+"\n";
    return -1;
  }

  fireidV->set_cur(recno);
  fireidV->get(&fireid, 1);
  return 0;
};

// read-in fire 'severity', for ONE record only
void CohortInputer::getFireSeverity(int fseverity[], const int & recid) {
  NcError err(NcError::silent_nonfatal);
  NcFile fireFile(firefname.c_str(), NcFile::ReadOnly);
  NcVar* fsevV = fireFile.get_var("SEVERITY");

  if(fsevV==NULL) {
    string msg = "Cannot get fire SEVERITY in 'fire.nc'! ";
    cout<<msg+"\n";
    exit(-1);
  }

  fsevV->set_cur(recid);
  NcBool nb = fsevV->get(&fseverity[0], 1, md->act_fireset);

  if(!nb) {
    string msg = "problem in reading fire SEVERITY in 'fire.nc'! ";
    cout<<msg+"\n";
    exit(-1);
  }
};
