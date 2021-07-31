library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;

entity memDatos is
    generic (
        p : integer := 9;
        d : integer := 16
    );
    Port ( add : in STD_LOGIC_VECTOR (p-1 downto 0);
           dataIn : in STD_LOGIC_VECTOR (d-1 downto 0);
           WD,clk : in STD_LOGIC;
           dataOut : out STD_LOGIC_VECTOR (d-1 downto 0));
end memDatos;

architecture arq_memDatos of memDatos is
type mem is array (0 to (2**p)-1) of STD_LOGIC_VECTOR (d-1 downto 0);
signal caja : mem;-- := (
  -- others => (others => '0')
--);
begin
    process(clk)
    begin
        if (rising_edge(clk)) then
            if (WD ='1') then
                caja(conv_integer(add)) <= dataIn;
            end if;
        end if;
    end process;
    dataOut <= caja(conv_integer(add));
end arq_memDatos;