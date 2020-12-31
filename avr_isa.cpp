#include  "avr_isa.H"
#include  "avr_isa_init.cpp"
#include  "avr_bhv_macros.H"

//If you want debug information for this model, uncomment next line
//#define DEBUG_MODEL
#include "ac_debug_model.H"

// 'using namespace' statement to allow access to all
// avr-specific datatypes
using namespace avr_parms;

static int processors_started = 0;
#define DEFAULT_STACK_SIZE (256*1024)

//!Generic instruction behavior method.
void ac_behavior(instruction)
{
  dbg_printf("----- PC=%#x ----- %lld\n", (int) ac_pc, ac_instr_counter);
  //  dbg_printf("----- PC=%#x NPC=%#x ----- %lld\n", (int) ac_pc, (int)npc, ac_instr_counter);
#ifndef NO_NEED_PC_UPDATE
  ac_pc = npc;
  npc = ac_pc + 4;
#endif
};

//! Instruction Format behavior methods.
void ac_behavior( Type_R ){}
void ac_behavior( Type_I ){}
void ac_behavior( Type_S ){}

//!Behavior called before starting simulation
void ac_behavior(begin)
{
  dbg_printf("@@@ begin behavior @@@\n");
  RB[0] = 0;
  npc = ac_pc + 4;

  // Is is not required by the architecture, but makes debug really easier
  for (int regNum = 0; regNum < 16; regNum ++)
    RB[regNum] = 0;
}

//!Behavior called after finishing simulation
void ac_behavior(end)
{
  dbg_printf("@@@ end behaviour @@@\n");
}

//!Metodo do comportamento da instrucao ld.w
void ac_behavior( ldw )
{
   switch(stage){
	case IF:
	    IF_ID.npc = ac_pc + 4;
            break;
        case ID:
            break;
        case EX:
	    int rs, resultadoULA;
            rs = RB[ID_EX.rs];
	    resultadoULA = rs + 4;
            RB.write(RB[ID_EX.rd],DM.read(resultadoULA);
            break;
        default:
            break;
    };
};

//!Metodo do comportamento da instrucao st.w
void ac_behavior( sw )
{
    switch(stage){
        case IF:
	    IF_ID.npc = ac_pc + 4;
            break;
        case ID:
            break;
        case EX:
	    int rd, rs, resultadoULA;
            rs = RB[ID_EX.rs];
            rd = RB[ID_EX.rd];
            resultadoULA = rs + 4;
            DM.write(resultadoULA, rd);
            break;
        default:
            break;
    };
};

//!Metodo do comportamento da instrucao subi
void ac_behavior( subi )
{
    switch(stage){
        case IF:
	    IF_ID.npc = ac_pc + 4;
            break;
        case ID:
	    ID_EX.imm = IF_ID.k2017;
            ID_EX.imm = ID_EX.imm << 1;
	    ID_EX.imm = ID_EX.imm | IF_ID.k16;
	    ID_EX.imm = ID_EX.imm << 16;
	    ID_EX.imm = ID_EX.imm | IF_EX.k1500;
	    ID_EX.imm = ID_EX.imm & 0xFFFF;
	    break;
        case EX:
            int rd, resultadoULA;
	    rd = RB[ID_EX.rd];
            resultadoULA = rd - EX_ULA.imm;
            RB.write(ID_EX.rd, MUL_LS.resultadoULA);
            break;
        default:
            break;
    };
};

//!Metodo do comportamento da instrucao add
void ac_behavior( add ){
    switch(stage){
    case IF:
	IF_ID.npc = ac_pc + 4;
        break;
    case ID:
        break;
    case EX:
        int rs, rd, resultadoULA;
	rs = RB.read(ID_EX.rs);
        rd = RB.read(ID_EX.rd);
        resultadoULA = rs + rd;
        RB.write(ID_EX.rd, resultadoULA);
        break;
    default:
        break;
    };
};

//!Metodo do comportamento da instrucao sub
void ac_behavior( sub )
{
  switch(stage){
        case IF:
	    IF_ID.npc = ac_pc + 4;
            break;
        case ID:
            break;
        case EX:
            int rs, rd, resultadoULA;
	    rs = RB.read(ID_EX.rs);
            rd = RB.read(ID_EX.rd);
            resultadoULA = rd - rs;
            RB.write(ID_EX.rd, resultadoULA);
            break;
        default:
            break;
    };
};

//!Metodo do comportamento da instrucao and
void ac_behavior( instr_and )
{
  switch(ac_stage_list){
        case IF:
	    IF_ID.npc = ac_pc + 4;
            break;
        case ID:
            break;
        case EX:
            int rs, rd, resultadoULA;
            rs = RB.read(ID_EX.rs);
            rd = RB.read(ID_EX.rd);
            resultadoULA = rd & rs;
            RB.write(ID_EX.rd, resultadoULA);
            break;
        default:
            break;
    };
};

//!Metodo do comportamento da instrucao mov
void ac_behavior( mov )
{
  switch(stage){
        case IF:
	    IF_ID.npc = ac_pc + 4;
            break;
        case ID:
	    ID_EX.imm = IF_ID.k2017;
            ID_EX.imm = ID_EX.imm << 1;
	    ID_EX.imm = ID_EX.imm | IF_ID.k16;
	    ID_EX.imm = ID_EX.imm << 16;
	    ID_EX.imm = ID_EX.imm | IF_EX.k1500;
	    ID_EX.imm = ID_EX.imm & 0xFFFF;
            break;
        case EX:
            RB.write(ID_EX.rd, ID_EX.imm);
            break;
        default:
            break;
    };
};

//!Metodo do comportamento da instrucao mul
void ac_behavior( mul )
{
    switch(stage){
        case IF:
	    IF_ID.npc = ac_pc + 4;
            break;
        case ID:
            break;
        case EX:
            int rs, rd, resultado MUL;
	    rs = RB.read(ID_EX.rs);
            rd = RB.read(ID_EX.rd);
            resultadoMUL = rs * rd;
            RB.write(ID_EX.rd, resultadoMUL);
            break;
        default:
	    break;
   };
};

//!Metodo do comportamento da instrucao divs
void ac_behavior( divs )
{
    switch(stage){
        case IF:
	    IF_ID.npc = ac_pc + 4;
            break;
        case ID:
            break;
        case EX:
	    int rs, rd, resultadoULA;
            rs = RB.read(ID_EX.rs);
            rd = RB.read(ID_EX.rd);
            resultadoULA = rs / rd ;
            RB.write(ID_EX.ry, resultadoULA);
            break;
        default:
	    break;
    };
};
