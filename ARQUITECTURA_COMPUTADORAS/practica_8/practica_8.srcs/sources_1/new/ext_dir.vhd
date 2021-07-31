library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity ext_dir is
  Port (
    dir: in STD_LOGIC_VECTOR(11 downto 0);
    dirExt: out STD_LOGIC_VECTOR(15 downto 0)
   );
end ext_dir;

architecture arq_ext_dir of ext_dir is    
begin
    dirExt(15 downto 12) <= "0000";
    dirExt(11 downto 0) <= dir;
end arq_ext_dir;
