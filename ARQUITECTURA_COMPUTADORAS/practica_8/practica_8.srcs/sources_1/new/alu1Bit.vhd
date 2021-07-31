library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity alu1Bit is
 Port (
    a,b,sela,selb,cin: in STD_LOGIC;
    res,co: out STD_LOGIC;
    op: in STD_LOGIC_VECTOR(1 downto 0) 
 );
end alu1Bit;

architecture arq_alu1Bit of alu1Bit is
component sum1Bit is
    Port ( a,b,ci : in STD_LOGIC;
           s,co : out STD_LOGIC);
end component;
signal auxa, auxb, auxand, auxor, auxxor, suma: STD_LOGIC;
begin
    -- Salidas de los multiplexores de A y B
    auxa <= a xor sela;
    auxb <= b xor selb;
    -- Operaciones posibles
    auxand <= auxa and auxb;
    auxor <= auxa or auxb;
    auxxor <= auxa xor auxb;
    sumador: sum1Bit port map(
        a => auxa,
        b => auxb,
        ci => cin,
        s => suma,
        co => co
    );
    -- Descripcion del multiplexor de salida de la ALU
    process (auxand, auxor, auxxor, suma, op)
    begin
        case op is
            when "00" => res <= auxand;
            when "01" => res <= auxor;
            when "10" => res <= auxxor;
            when others => res <= suma;
        end case;
    end process;
end arq_alu1Bit;
