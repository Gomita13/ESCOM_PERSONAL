library IEEE;
library work;
use IEEE.STD_LOGIC_1164.ALL;
use work.paqueteCPU.ALL;

--La siguiente entidad contiene todos los elementos del procesador que hemos revisado
--unicamente es necesario conectar la unidad de control para el funcionamiento completo de un CPU.
--Las entradas y salidas aqui descritas corresponden a las mismas que proporciona la unidad de control.
entity cpu is
    Port (
        CLK,CLR,UP,DW,WPC,SDMP,SR2,SWD,SEXT,SOP1,SOP2,SDMD,WD,SR,SHE,DIR,WR: in STD_LOGIC;
        ALUOP: in STD_LOGIC_VECTOR(3 downto 0);
        INS1, FLAGS: out STD_LOGIC_VECTOR(3 downto 0);
        INS2: out STD_LOGIC_VECTOR(4 downto 0)
    );
end cpu;

architecture arq_cpu of cpu is
signal SP: STD_LOGIC_VECTOR(2 downto 0);
signal iPILA,oPILA: STD_LOGIC_VECTOR(15 downto 0); --in y out DE LA PILA
signal oMEPR: STD_LOGIC_VECTOR(24 downto 0); --out DE LA MEMORIA DE PROGRAMA
-- in PARA ARCHIVO DE REGISTROS
signal READREG1, READREG2, WRITEREG, SHAMT: STD_LOGIC_VECTOR(3 downto 0);
signal WRITEDATA,READDATA1, READDATA2: STD_LOGIC_VECTOR(15 downto 0);
signal oSR,oSEXT,oSOP1, oSOP2, oALU: STD_LOGIC_VECTOR(15 downto 0); -- salida de multiplexores para ALU y salida ALU
signal oMEDA,oEXS, oEXD: STD_LOGIC_VECTOR(15 downto 0);
signal oSDMD: STD_LOGIC_VECTOR(9 downto 0);
begin
--Multiplexor SR
oSR <= oMEDA when (SR = '0') else oALU;
-- Instancia Pila
--Agregando el multiplexor
iPILA <= oMEPR(15 downto 0) when (SDMP = '0') else oSR;
pila_hw: pila 
    port map( 
        clk => CLK,
        clr => CLR,
        up => UP,
        dw => DW,
        wpc => WPC,
        spOut => SP,
        pcIn => iPILA,
        pcOut => oPILA
    );
--Instancia Memoria Programa
mem_prog: memProg 
    port map(
        pc => oPILA(9 downto 0),
        inst => oMEPR
    );
--Intancia Archivo de Registros
--Algunas operaciones para poder establecer correctamente las entradas
READREG1 <= oMEPR(15 downto 12);
READREG2 <= oMEPR(11 downto 8) when (SR2 = '0') else oMEPR(19 downto 16);
WRITEREG <= oMEPR(19 downto 16);
SHAMT <= oMEPR(7 downto 4);
WRITEDATA <= oMEPR(15 downto 0) when (SWD = '0') else oSR;
file_reg: fileReg port map(
    writeData => WRITEDATA,
    writeReg => WRITEREG,
    readReg1 => READREG1,
    readReg2 => READREG2,
    shamt => SHAMT,
    clk => CLK,
    clr => CLR,
    wr => WR,
    dir => DIR,
    she => SHE,
    readData1 => READDATA1,
    readData2 => READDATA2
    );
    
 --Instancia de los extensores
 ext_sig: ext_signo port map(
    lit => oMEPR(11 downto 0),
    litExt => oEXS
 );
 
 ext_di: ext_dir port map(
    dir => oMEPR(11 downto 0),
    dirExt => oEXD 
 );
 
 -- Instancia de la ALU
 --Agregando multiplexores
 oSEXT <= oEXS when (SEXT = '0') else oEXD;
 oSOP1 <= READDATA1 when (SOP1 = '0') else oPILA;
 oSOP2 <= READDATA2 when (SOP2 = '0') else oSEXT;
 alu1: alu port map(
    a => oSOP1,
    b => oSOP2,
    co => FLAGS(3),
    ov => FLAGS(2),
    z => FLAGS(1),
    n => FLAGS(0),
    op => ALUOP,
    s => oALU 
 );
 --Instancia de la memoria de datos
 oSDMD <= oALU(9 downto 0) when (SDMD = '0') else oMEPR(9 downto 0);
datos: memDatos port map(
    add => oSDMD(9 downto 0),
    dataIn => READDATA2,
    wd => WD,
    clk => CLK,
    dataOut => oMEDA 
);
INS1 <= oMEPR(3 downto 0);
INS2 <= oMEPR(24 downto 20);
end arq_cpu;
