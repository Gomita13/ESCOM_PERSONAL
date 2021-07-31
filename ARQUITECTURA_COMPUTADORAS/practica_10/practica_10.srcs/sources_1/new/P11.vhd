library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use WORK.PaqueteUC.ALL;
entity P11 is
    port (
    opcode : in STD_LOGIC_VECTOR (4 downto 0);
    funcode,Banderas : in STD_LOGIC_VECTOR (3 downto 0);
    CLR,CLK,LF: in STD_LOGIC;
    MicroInstruccion: out std_logic_vector (19 downto 0)
    );
end P11;

architecture Behavioral of P11 is
signal muxSDOPC: std_logic_vector (4 downto 0);
signal TIPOR,BEQI,BNEQI,BLTI,BLETI,BGTI,BGETI,EQ,NE,LT,LE,GT,GE,NA,SDOPC,SM: STD_LOGIC;
signal Q : STD_LOGIC_VECTOR (3 downto 0);
signal MicroOP,MicroFUN: std_logic_vector (19 downto 0);
begin
    i_UC: UC port map (
        TIPOR=>TIPOR,
        BEQI => BEQI,
        BNEQI => BNEQI,
        BLTI=> BLTI,
        BLETI=>BLETI,
        BGTI=>BGTI,
        BGETI=>BGETI,
        NA=>NA,
        EQ=>EQ,
        NE=>NE,
        LT=>LT,
        LE=>LE,
        GT=>GT,
        GE=>GE,
        CLR=>CLR,
        CLK=>CLK,
		SDOPC=>SDOPC,
		SM=>SM
    );
    i_Registro: Registro port map(
        d(3) => Banderas(3), --OV
        d(2) => Banderas(1), --Z
        d(1) => Banderas(0), --C
        d(0) => Banderas(2),--N
        clr=>CLR,
        clk => CLK,
        LF => LF,
        q => Q
    );
    i_Nivel: Nivel port map (
        CLR=> CLR, 
        CLK => CLK,
        NA => NA
    );
    muxSDOPC <= opcode when SDOPC = '1' else "00000";
    i_MopCode: MopCode port map (
        opcode => muxSDOPC,
        MicroInstruccion => MicroOP
    );
    i_MfunCode: MfunCode port map (
        funCode => funcode,
        MicroInstruccion => MicroFUN
    );    
    i_Decodificador: decod port map (
        opCode => opcode,
        TIPOR=>TIPOR,
        BEQI=>BEQI,
        BNEQI=>BNEQI,
        BLTI=>BLTI,
        BLETI=>BLETI,
        BGTI=>BGTI,
        BGETI=>BGETI
    );
    i_Condicion: Condicion port map (
        Q => Q,
        EQ=>EQ,
        NE=>NE,
        LT=>LT,
        LE=>LE,
        GT=>GT,
        GE=>GE
    );
    MicroInstruccion <= MicroFUN when SM ='0' else MicroOP;
end Behavioral;
