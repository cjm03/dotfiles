vim.cmd("set expandtab")
vim.cmd("set tabstop=4")
vim.cmd("set softtabstop=4")
vim.cmd("set shiftwidth=4")
vim.cmd("set termguicolors")

-- options
vim.opt.swapfile = false
vim.opt.relativenumber = true
vim.opt.number = true
vim.opt.wrap = false
vim.opt.cursorline = false
vim.opt.scrolloff = 10
vim.opt.fillchars:append { eob = " " }
vim.opt.clipboard:append("unnamedplus")


-- keymaps
vim.g.mapleader = " "
vim.keymap.set('i', 'jk', '<ESC>', { desc = "exit insert mode" })




-- tabs
vim.keymap.set('n', '<leader>to', '<cmd>tabnew<CR>', { desc = "Open new tab" })
vim.keymap.set('n', '<leader>tx', '<cmd>tabclose<CR>', { desc = "Close current tab" })
vim.keymap.set('n', '<leader>tn', '<cmd>tabn<CR>', { desc = "Go to next tab" })
vim.keymap.set('n', '<leader>tp', '<cmd>tabp<CR>', { desc = "Go to previous tab" })
vim.keymap.set('n', '<leader>tf', '<cmd>tabnew %<CR>', { desc = "Open current buffer in new tab" })
