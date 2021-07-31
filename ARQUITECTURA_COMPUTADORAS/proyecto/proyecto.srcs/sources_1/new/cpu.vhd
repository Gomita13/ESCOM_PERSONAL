library IEEE;
library WORK;
use IEEE.STD_LOGIC_1164.ALL;
use WORK.paqueteCPU.ALL;

entity ESCOMips is
    Port ( rclr,clk: in STD_LOGIC;
           reDa1,reDa2,busSR,resALU: out std_logic_vector (15 downto 0);
           PC : out std_logic_vector (9 downto 0);
           instruccion: out std_logic_vector (24 downto 0);
           Micro: out std_logic_vector(19 downto 0)
     );
end ESCOMips;

architecture arq_ESCOMips of ESCOMips is
signal outPILA,readData1,readData2,outALU,outMemDa,exSig,exDir: std_logic_vector (15 downto 0) := (others => '0');
signal CLR: std_logic;
signal ALUOP,FLAGS : STD_LOGIC_VECTOR (3 downto 0) := (others => '0');
signal muxSR,muxSDMP,muxSWD,muxSOP1,muxSOP2,muxSEXT: std_logic_vector (15 downto 0) := (others => '0');
signal muxSR2: std_logic_vector (3 downto 0) := (others => '0');
signal muxSDMD: std_logic_vector (8 downto 0) := (others => '0');
signal Inst: std_logic_vector (24 downto 0) := (others => '0');
signal Cout: std_logic;
signal sMICRO : STD_LOGIC_VECTOR (19 downto 0) := (others => '0');
begin
    process (CLK) 
        begin
            if (falling_edge(CLK)) then
                CLR <= RCLR;
            end if;
    end process;  

exSig <= Inst(11) & Inst(11) & Inst(11) & Inst(11) & Inst(11 downto 0);
exDir <= "0000" & Inst(11 downto 0);
muxSR <= outMemDa(15 downto 0) when (sMICRO (1)='0') else outALU;
muxSDMP <= Inst(15 downto 0) when (sMICRO (19)='0') else muxSR; 
muxSR2 <= Inst(11 downto 8) when (sMICRO (15)='0') else Inst(19 downto 16);
muxSWD <= Inst(15 downto 0) when (sMICRO (14)='0') else muxSR;
muxSOP1 <= readData1 when (sMICRO (9)='0') else outPILA;
muxSEXT <= exSig when (sMICRO (13)='0') else exDir;
muxSOP2 <= readData2 when (sMICRO (8)='0') else muxSEXT;
muxSDMD <= outALU(8 downto 0) when (sMICRO (3)='0') else Inst(8 downto 0);
    
    iPila: pila port map (
        clk => CLK,
        clr => CLR,
        up => sMICRO (18),
        dw => sMICRO (17),
        WPC => sMICRO (16),
        pcin => muxSDMP,
        pcout => outPILA    
    );  
    imemProg: memProg port map (
        PC =>  outPILA(8 downto 0),
        Inst => Inst
    ); 
    iArchivoDeRegistros: fileReg port map (
        clr => CLR,
        clk => CLK,
        WR => sMICRO (10),
        SHE => sMICRO (12),
        DIR => sMICRO (11),
        writeReg => Inst(19 downto 16),
        readReg1 => Inst(15 downto 12),
        readReg2 => muxSR2,
        shamt => Inst(7 downto 4),
        writeData => muxSWD,
        readData1 => readData1,
        readData2 => readData2
    );
    
    iALU: alu port map (
        a => muxSOP1,
        b => muxSOP2,
        OP => sMICRO (7 downto 4),
        s => outALU,
        co => FLAGS(3),
        n => FLAGS(2),
        ov => FLAGS(1),
        z => FLAGS(0)        
    );
    
    imemDatos: memDatos port map(
        add => muxSDMD,
        dataIn => readData2,
        WD => sMICRO (2),
        clk => CLK,
        dataOut => outMemDa      
    );
    
    UC: P11 port map (
        opcode => Inst(24 downto 20),
        funcode => Inst(3 downto 0),
        Banderas(3) => FLAGS (1) ,--OV
        Banderas (2) => FLAGS (2),--N
        Banderas (1) => FLAGS (0),--Z
        Banderas (0)=> FLAGS (3),--C
        CLR => CLR,
        CLK => CLK,
        MicroInstruccion => sMICRO
    );

    Instruccion <= Inst;
    PC <= outPILA (9 downto 0);
    reDa1<= readData1;
    reDa2 <= readData2;
    resAlu <= outALU;
    BusSR <= muxSR;
    Micro <= sMICRO;

end arq_ESCOMips;
