library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity tb_deco is
end tb_deco;

architecture arq_tb_deco of tb_deco is
component deco is
  Port (
    A: in STD_LOGIC_VECTOR(3 downto 0);
    B: out STD_LOGIC_VECTOR(6 downto 0)
  );
end component;
signal sA: STD_LOGIC_VECTOR(3 downto 0);
signal sB: STD_LOGIC_VECTOR(6 downto 0);
begin

instancia: deco port map(
    A => sA,
    B => sB
);

process
begin
    sA <= "0000";
    wait for 2 ns;
    sA <= "0001";
    wait for 2 ns;
    sA <= "0010";
    wait for 2 ns;
    sA <= "0011";
    wait for 2 ns;
    sA <= "0100";
    wait for 2 ns;
    sA <= "0101";
    wait for 2 ns;
    sA <= "0110";
    wait for 2 ns;
    sA <= "0111";
    wait for 2 ns;
    sA <= "1000";
    wait for 2 ns;
    sA <= "1001";
    wait for 2 ns;
end process;

end arq_tb_deco;
