library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_arith.ALL;
use IEEE.STD_LOGIC_unsigned.ALL;


entity pila is
    generic (
        p: integer := 16;
        q: integer := 8
    );
    Port ( 
        clk, clr, up, dw, wpc : in  STD_LOGIC;
        pcin : in  STD_LOGIC_VECTOR (p-1 downto 0);
        pcout : out  STD_LOGIC_VECTOR (p-1 downto 0)
    );
end pila;

architecture arq_pila of pila is
type contadores is array (0 to q-1) of std_logic_Vector(p-1 downto 0);
signal pila : contadores;
begin
    process(clk, clr, pila) 
    variable sp : integer range 0 to q-1 := 0;
    begin
        if (clr = '1') then
            sp := 0;
            pila <= (others => (others => '0'));
        elsif (rising_edge(clk)) then
            if (wpc = '0' and up = '0' and dw = '0') then --Incremento
                sp := sp;
                pila(sp) <= pila(sp) + 1;
            elsif (wpc = '1' and up = '0' and dw = '0') then --Saltos
                sp := sp;
                pila(sp) <= pcin;
            elsif (wpc = '1' and up = '1' and dw = '0') then --CALL
                sp := sp + 1;
                pila(sp) <= pcin;
            elsif (wpc = '0' and up = '0' and dw = '1') then --RET
                sp := sp - 1;
                pila(sp) <= pila(sp) + 1;
            end if;
        end if;
        pcout <= pila(sp);
    end process;
end arq_pila;