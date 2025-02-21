vim.g.loaded_netrw = 1
vim.g.loaded_netrwPlugin = 1


local lazypath = vim.fn.stdpath("data") .. "/lazy/lazy.nvim"
if not vim.loop.fs_stat(lazypath) then
	vim.fn.system({
		"git",
		"clone",
		"--filter=blob:none",
		"https://github.com/folke/lazy.nvim.git",
		"--branch=stable",
		lazypath,
	})
end
vim.opt.rtp:prepend(lazypath)

require("vimopts")
require("lazy").setup("plugins")

--vim.api.nvim_set_h1(0, 'LineNr', { fg = '#5c6370', bg = '#16181d' }) -- Muted gray text on bg0
--vim.api.nvim_set_h1(0, 'SignColumn', { fg= '#5c6370', bg = '#16181d' }) -- Same for sign column
--vim.api.nvim_set_h1(0, 'CursorLineNr', { fg = '#adbac7', bg = '#16181d' }) -- Highlighted line number color



