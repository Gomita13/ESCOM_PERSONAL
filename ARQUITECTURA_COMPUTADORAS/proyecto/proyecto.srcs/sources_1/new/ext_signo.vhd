library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity ext_signo is
    Port(
        lit: in STD_LOGIC_VECTOR(11 downto 0);
        litExt: out STD_LOGIC_VECTOR(15 downto 0)
    );
end ext_signo;

architecture arq_ext_signo of ext_signo is
begin
process (lit)
begin
    if (lit(11) = '0') then
        litExt(15 downto 12) <= "0000";
    else
        litExt(15 downto 12) <= "1111";
    end if;
    litExt(11 downto 0) <= lit;
end process;
end arq_ext_signo;
