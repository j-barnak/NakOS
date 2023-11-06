require("lspconfig").clangd.setup({
	on_new_config = function(config)
		config.cmd = {
			"clangd",
			"--background-index",
			"--query-driver",
			"/home/jared/Projects/NakOS/Toolchain/opt/cross/bin/i686-elf-g++",
		}
	end,
})
