return {
    "nvim-treesitter/nvim-treesitter",
    build = ":TSUpdate",
    config = function()
        local configs = require("nvim-treesitter.configs")
        configs.setup({
            ensure_installed = { "c", "lua", "vim", "vimdoc", "markdown", "asm", "css", "csv", "python", "rust", "regex", },
            highlight = { enable = true },
            indent = { enable = false },
        })
    end
}
