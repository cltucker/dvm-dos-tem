#ifndef ERRORCODE_H_
#define ERRORCODE_H_
enum ERRORKEY { I_VAR_NULL =1, I_INPUT_INVALID,
                I_TEM_TSTEP_SMALL=20, I_BOTTOM_NEW_FRONT, I_NAN_TLD, I_NAN_TIT,
                I_NAN_TII,I_TOO_BIG_TII,I_TOO_SMALL_TII,
                I_WAT_TSTEP_SMALL=30, I_NAN_WATER, I_NEG_WATER,
                I_TOO_MANY_FRZ_FRONTS=41,  I_TOO_MANY_THW_FRONTS,
                I_FRONT_INCONSISTENT, I_FROZEN_STATE, I_GROW_START, I_SNOW_AGE,
                I_NIMMOB_RANGE=50,I_NUPTAKE_RANGE,
                I_BURN_ZERO =60,
                I_LAYER_FIRST_DEEP=70, I_FRONT_STATE_INCON,  I_FRONT_POSITION,
                I_NCFILE_NOT_EXIST=100, I_NCDIM_NOT_EXIST, I_NCVAR_NOT_EXIST,
                I_NCVAR_GET_ERROR
              };

const int MISSING_I    = -9999;    //missing value (INT) used in the code
const float MISSING_F  = -9999.f;  //missing value (FLOAT) used in the code
const double MISSING_D = -9999.;   //missing value (DOUBLE) used in the code

#ifndef NULL
#define NULL   ((void *) 0)
#endif

#endif /*ERRORCODE_H_*/
