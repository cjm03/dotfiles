return {
    "neovim/nvim-lspconfig",
    event = { "BufReadPre", "BufNewFile" },
    dependencies = {
        "hrsh7th/cmp-nvim-lsp",
    },
    config = function()
        local lspconfig = require("lspconfig")
        local cmp_nvim_lsp = require("cmp_nvim_lsp")
        local keymap = vim.keymap
        local opts = { noremap = true, silent = true }
        local on_attach = function(client, bufnr)
            opts.buffer = bufnr
            opts.desc = "Show LSP references"
            keymap.set('n', '<leader>lr', '<cmd>Telescope lsp_references<CR>', opts)

            opts.desc = "Go to declaration"
            keymap.set('n', '<leader>lD', vim.lsp.buf.declaration, opts)

            opts.desc = "Show LSP definitions"
            keymap.set('n', '<leader>ld', '<cmd>Telescope lsp_definitions<CR>', opts)

            opts.desc = "Show LSP implementations"
            keymap.set('n', '<leader>li', '<cmd>Telescope lsp_implementations<CR>', opts)

            opts.desc = "Show LSP type definitions"
            keymap.set('n', '<leader>lt', '<cmd>Telescope lsp_type_definitions<CR>', opts)

            opts.desc = "Show documentation for what is under cursor"
            keymap.set('n', '<leader>lk', vim.lsp.buf.hover, opts)
        end

        local capabilities = cmp_nvim_lsp.default_capabilities(vim.lsp.protocol.make_client_capabilities())

        require("lspconfig").clangd.setup({
            cmd = {
                "clangd",
                "--background-index",
                "--clang-tidy",
                "--log=verbose",
                "--header-insertion=iwyu",
                "--completion-style=detailed",
                "--function-arg-placeholders",
                "--fallback-style=llvm",
            },
            init_options = {
                usePlaceholders = true,
                completeUnimported = true,
                clangdFileStatus = true,
            },
            filetypes = { "c", "objc" },
            root_dir = require("lspconfig").util.root_pattern(".clandg"),
            capabilities = capabilities,
            on_attach = on_attach,
        })

        lspconfig["pylsp"].setup({
            capabilities = capabilities,
            on_attach = on_attach,
        })

        lspconfig["lua_ls"].setup({
            capabilities = capabilities,
            on_attach = on_attach,
            settings = {
                Lua = {
                    diagnostics = {
                        globals = { "vim" },
                    },
                }
            }
        })
    end,
}
