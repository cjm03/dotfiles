--return {
--   "nvim-neo-tree/neo-tree.nvim",
--   branch = "v3.x",
--   dependencies = {
--       "nvim-lua/plenary.nvim",
--       "nvim-tree/nvim-web-devicons",
--       "MunifTanjim/nui.nvim",
--   },
--   config = function()
--       require("neo-tree").setup({
--           filesystem = {
--               filtered_items = {
--                   hide_hidden = false,
--                   hide_dotfiles = false,
--               },
--           },
--       })
--       vim.keymap.set('n', '<leader>ee', ':Neotree filesystem reveal left<CR>', { desc = "reveal/activate file explorer" })
--       vim.keymap.set('n', '<leader>ex', ':Neotree filesystem toggle<CR>', { desc = "Expand/collapse file explorer" })
--   end
--}

return {
    "nvim-tree/nvim-tree.lua",
    enabled = false,
    dependencies = "nvim-tree/nvim-web-devicons",
    config = function()
        local nvimtree = require("nvim-tree")

        vim.g.loaded_netrw = 1
        vim.g.loaded_netrwPlugin = 1

        nvimtree.setup({
            hijack_directories = {
                enable = false, -- Set this to false if you want to disable it
                auto_open = false, -- Automatically open the tree when switching to a directory
            },
            view = {
                width = 35,
                relativenumber = true,
                side = "left",
            },
            -- change folder arrow icons
            renderer = {
                indent_markers = {
                    enable = true,
                },
                icons = {
                    glyphs = {
                        folder = {
                            arrow_closed = "→", -- arrow when folder is closed
                            arrow_open = "↓", -- arrow when folder is open
                        },
                    },
                },
            },
            -- disable window_picker for
            -- explorer to work well with
            -- window splits
            actions = {
                open_file = {
                    window_picker = {
                        enable = false,
                    },
                },
            },
            filters = {
            },
            git = {
                ignore = false,
            },
        })

        -- ** Opens nvim file tree at start
        -- if vim.fn.argc(-1) == 0 then
        --     vim.cmd("NvimTreeFocus")
        -- end

        -- keymaps
        local keymap = vim.keymap                                                                                         -- for conciseness

        keymap.set("n", "<leader>ee", "<cmd>NvimTreeToggle<CR>", { desc = "Toggle file explorer" })     -- toggle file explorer
        keymap.set("n", "<leader>ex", "<cmd>NvimTreeCollapse<CR>", { desc = "Collapse file explorer" }) -- collapse file explorer
        keymap.set("n", "<leader>er", "<cmd>NvimTreeRefresh<CR>", { desc = "Refresh file explorer" })   -- refresh file explorer
    end
}
