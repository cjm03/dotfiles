return {
    "nvim-lualine/lualine.nvim",
    dependencies = { "echasnovski/mini.icons" },
    config = function()
        require("lualine").setup({
            options = {
                icons_enabled = true,
                theme = "iceberg_dark",
--                theme = "ayu_mirage",
--                theme = "onedark-nvim",
                section_separators = '',
                component_separators = '',
            },
        })
    end
}
