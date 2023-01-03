library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

ENTITY FAYARD_Lab1 IS
   PORT(
      clk	: in  std_logic;
      reset	: in  std_logic;
		pio_0 : out std_logic_vector(7 downto 0);
		pio_1 : in std_logic_vector(3 downto 0)
      );
END FAYARD_Lab1;


ARCHITECTURE ARCH_FAYARD_Lab1 OF FAYARD_Lab1 IS

component Lab1_sys is
	port (
		clk_clk                          : in  std_logic                    := 'X';             -- clk
		pio_0_external_connection_export : out std_logic_vector(7 downto 0);                    -- export
		pio_1_external_connection_export : in  std_logic_vector(3 downto 0) := (others => 'X'); -- export
		reset_reset_n                    : in  std_logic                    := 'X'              -- reset_n
        );
end component Lab1_sys;

begin
	u0 : component Lab1_sys
		port map (
			clk_clk                          => clk,                          -- clk.clk
			pio_0_external_connection_export => pio_0, 								-- pio_0_external_connection.export
			pio_1_external_connection_export => pio_1, 								-- pio_1_external_connection.export
			reset_reset_n                    => reset                     		-- reset.reset_n
			  );
END ARCH_FAYARD_Lab1;