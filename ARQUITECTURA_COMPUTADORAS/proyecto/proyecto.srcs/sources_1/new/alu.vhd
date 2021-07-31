library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity alu is
    generic (
        p: integer := 16
    );    
    Port ( 
    a,b: in STD_LOGIC_VECTOR(p-1 downto 0);
    --Recordamos que co = c
    co,ov,z,n: out STD_LOGIC;
    --Recordamos cin = selb = op(2)
    op: in STD_LOGIC_VECTOR(3 downto 0);
    s : out STD_LOGIC_VECTOR(p-1 downto 0)
);
  -- Recordamos que op es un canal que concatena sela+selb+op1+op0
  -- En este orden vamos a leer 	los datos a ingresar a la ALU
end alu;

architecture aqr_alu of alu is
component alu1Bit is
 Port (
    a,b,sela,selb,cin: in STD_LOGIC;
    res,co: out STD_LOGIC;
    op: in STD_LOGIC_VECTOR(1 downto 0));
end component;
signal auxop: STD_LOGIC_VECTOR(1 downto 0) := (others => '0');
signal auxco: STD_LOGIC_VECTOR(p downto 0) := (others => '0');
signal auxs: STD_LOGIC_VECTOR(p-1 downto 0) := (others => '0');
begin
    -- Establecemos los acarreos
    auxco(0) <= op(2);
    co <= auxco(4) when op = "0011" else auxco(4) when op = "0111" else '0';
    --Generamos 4 ALUs de 1 Bit
    isntancias: for i in 0 to p-1 generate
        -- Recordamos que op(3) = sela, op(2) = selb, op(1) = op1, op(0) = op0
        alu: alu1Bit port map(
            a => a(i),
            b => b(i),
            sela => op(3),
            selb => op(2),
            cin => auxco(i),
            op(1) => op(1),
            op(0) => op(0),
            res => auxs(i),
            co => auxco(i+1)
        );
    end generate;
    ov <= auxco(p-1) xor auxco(p) when op = "0011" else auxco(p-1) xor auxco(p) when op = "0111" else '0';
    z <= not (auxs(15) or auxs(14) or auxs(13) or auxs(12)or auxs(11) or auxs(10) or auxs(9) or auxs(8) or auxs(7)or auxs(6) or auxs(5) or auxs(4) or auxs(3) or auxs(2) or auxs(1) or auxs(0));
    s <= auxs;
    n <= auxs(p-1);    
end aqr_alu;
