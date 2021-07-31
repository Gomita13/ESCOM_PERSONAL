library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity ESCOMips is
    Port(
        CLK,RCLR: in STD_LOGIC;
        PC,REDA1,REDA2,RESALU, BUSSR: out STD_LOGIC_VECTOR(15 downto 0);
        INST: out STD_LOGIC_VECTOR(24 downto 0)
    );
end ESCOMips;

architecture arq_ESCOMips of ESCOMips is
component P11 is
    port (
    opcode : in STD_LOGIC_VECTOR (4 downto 0);
    funcode,Banderas : in STD_LOGIC_VECTOR (3 downto 0);
    CLR,CLK: in STD_LOGIC;
    MicroInstruccion: out std_logic_vector (19 downto 0)
    );
end component;
component cpu is
    Port (
        CLK,CLR,UP,DW,WPC,SDMP,SR2,SWD,SEXT,SOP1,SOP2,SDMD,WD,SR,SHE,DIR,WR: in STD_LOGIC;
        ALUOP: in STD_LOGIC_VECTOR(3 downto 0);
        INS1, FLAGS: out STD_LOGIC_VECTOR(3 downto 0);
        INS2: out STD_LOGIC_VECTOR(4 downto 0);
        --PC,REDA1,REDA2,RESALU, BUSSR
        SALIDA1,SALIDA2,SALIDA3,SALIDA4,SALIDA5: out STD_LOGIC_VECTOR(15 downto 0);
        SALIDA6: out STD_LOGIC_VECTOR(24 downto 0)
    );
end component;
signal sOPCODE: STD_LOGIC_VECTOR(4 downto 0) := (others => '0'); 
signal sFUNCODE, sBANDERAS: STD_LOGIC_VECTOR(3 downto 0) := (others => '0');
signal sMICRO: STD_LOGIC_VECTOR(19 downto 0) := (others => '0');
signal CLR: STD_LOGIC := '0';
begin

iUC : P11 port map(
    opCode => sOPCODE,
    funcode => sFUNCODE,
    banderas => sBANDERAS,
    CLR => CLR,
    CLK => CLK,
    Microinstruccion => sMICRO
);

iCPU: cpu port map(
    CLK => CLK,
    CLR => CLR,
    SDMP => sMICRO(19),
    UP => sMICRO(18),
    DW => sMICRO(17), 
    WPC => sMICRO(16),
    SR2 => sMICRO(15),
    SWD => sMICRO(14),
    SEXT => sMICRO(13),
    SHE => sMICRO(12),
    DIR => sMICRO(11),
    WR => sMICRO(10),
    SOP1 => sMICRO(9),
    SOP2 => sMICRO(8),
    ALUOP => sMICRO(7 downto 4),
    SDMD => sMICRO(3),
    WD => sMICRO(2),
    SR => sMICRO(1),
    INS1 => sFUNCODE,
    FLAGS => sBANDERAS,
    INS2 => sOPCODE,
    SALIDA1 => PC,
    SALIDA2 => REDA1,
    SALIDA3 => REDA2,
    SALIDA4 => RESALU,
    SALIDA5 => BUSSR,
    SALIDA6 => INST
);

--process (CLK)
--begin
    --if (falling_edge(CLK)) then
    --    CLR <= RCLR;
  --  end if;
--end process;
end arq_ESCOMips;
