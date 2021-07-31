library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use WORK.PaqueteUC.ALL;
entity P11 is
    port (
    opcode : in STD_LOGIC_VECTOR (4 downto 0);
    funcode,Banderas : in STD_LOGIC_VECTOR (3 downto 0);
    CLR,CLK: in STD_LOGIC;
    MicroInstruccion: out std_logic_vector (19 downto 0)
    );
end P11;

architecture Behavioral of P11 is
signal muxSDOPC: std_logic_vector (4 downto 0);
signal TIPOR,BEQI,BNEQI,BLTI,BLETI,BGTI,BGETI,EQ,NE,LT,LE,GT,GE,NA,SDOPC,SM: STD_LOGIC := '0';
signal Q : STD_LOGIC_VECTOR (3 downto 0);
signal MicroOP,MicroFUN,sMicro: std_logic_vector (19 downto 0);
begin

    muxSDOPC <= opcode when (SDOPC = '1') else "00000";
    sMicro <= MicroFUN when SM ='0' else MicroOP;
    MicroInstruccion <= sMicro;
    
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
    
    i_Condicion: Condicion port map (
        Q => Q,
        EQ=>EQ,
        NE=>NE,
        LT=>LT,
        LE=>LE,
        GT=>GT,
        GE=>GE
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
    
    i_MfunCode: MfunCode port map (
        funCode => funcode,
        MicroInstruccion => MicroFUN
    );    
    
    i_MopCode: MopCode port map (
        opcode => muxSDOPC,
        MicroInstruccion => MicroOP
    );
    
    i_Nivel: Nivel port map (
        CLR=> CLR, 
        CLK => CLK,
        NA => NA
    );
    
    i_Registro: Registro port map(
        d(3) => Banderas(3), --OV
        d(2) => Banderas(1), --Z
        d(1) => Banderas(0), --C
        d(0) => Banderas(2),--N
        clr=>CLR,
        clk => CLK,
        LF => sMicro(0),
        q => Q
    );
    
end Behavioral;
