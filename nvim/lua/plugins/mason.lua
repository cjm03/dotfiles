return {
    "williamboman/mason.nvim",
    dependencies = {
        "williamboman/mason-lspconfig.nvim",
    },
    config = function()
        local mason = require("mason")
        local mason_lspconfig = require("mason-lspconfig")
        mason.setup({
            ui = {
                icons = {
                    package_installed = "Y",
                    package_pending = "-",
                    package_uninstalled = "X"
                }
            }
        })
        mason_lspconfig.setup({
            ensure_installed = {
                "clangd",
                "lua_ls",
                "pylsp"
            },
            automatic_installation = true,
        })
    end,
}
