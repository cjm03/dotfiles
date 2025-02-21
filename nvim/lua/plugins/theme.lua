--return {
--   "catppuccin/nvim",
--   lazy = false,
--   priority = 1000,
--   config = function()
--       require("catppuccin").setup({
--           flavour = "macchiato",
--           background = {
--               light = "macchiato",
--               dark = "macchiato",
--           },
--           transparent_background = true,
--       })
--       vim.cmd("colorscheme catppuccin")
--   end
--}

return {
    "folke/tokyonight.nvim",
    name = "folkeTokyonight",
    priority = 1000,
    config = function()
        local transparent = true
        local bg = "#011628"
        local bg_dark = "#011423"
        local bg_highlight = "#143652"
        local bg_search = "#0A64AC"
        local bg_visual = "#275378"
        local fg = "#CBE0F0"
        local fg_dark = "#B4D0E9"
        local fg_gutter = "#627E97"
        local border = "#547998"

        require("tokyonight").setup({
            style = "night",
            transparent = transparent,

            styles = {
                comments = { italic = false },
                keywords = { italic = false },
                sidebars = transparent and "transparent" or "dark",
                floats = transparent and "transparent" or "dark",
            },
            on_colors = function(colors)
                colors.bg = transparent and colors.none or bg
                colors.bg_dark = transparent and colors.none or bg_dark
                colors.bg_float = transparent and colors.none or bg_dark
                colors.bg_highlight = bg_highlight
                colors.bg_popup = bg_dark
                colors.bg_search = bg_search
                colors.bg_sidebar = transparent and colors.none or bg_dark
                colors.bg_statusline = transparent and colors.none or bg_dark
                colors.bg_visual = bg_visual
                colors.border = border
                colors.fg = fg
                colors.fg_dark = fg_dark
                colors.fg_float = fg
                colors.fg_gutter = fg_gutter
                colors.fg_sidebar = fg_dark
            end,
        })
        vim.cmd("colorscheme tokyonight")
    end
}


--return {
--    "vague2k/vague.nvim",
--    lazy = false,
--    priority = 1000,
--    config = function()
--        require("vague").setup({
--            style = {
--                comments = "none",
--                strings = "none",
--                variables = "bold",
--            },
--            colors = {
--                builtin = "#33cc33",
--                func = "#008000",
--                string = "#ff99cc",
--                number = "#ff3399",
--                property = "#33cc33",
--                constant = "#85e085",
--                operator = "#33cc33",
--                type = "#85e085",
--
--            },
--        })
--        vim.cmd("colorscheme vague")
--    end
--}


--return {
--    "rose-pine/neovim",
--    lazy = false,
--    priority = 1000,
--    name = "rose-pine",
--    config = function()
--        require("rose-pine").setup({
--            styles = { transparency = true },
--        })
--        vim.cmd("colorscheme rose-pine")
--    end
--}



--return {
--    "ful1e5/onedark.nvim",
--    lazy = false,
--    priority = 1000,
--    config = function()
--        require("onedark").setup({
--            comment_style = "NONE",
--            keyword_style = "NONE",
--            function_style = "NONE",
--            variable_style = "NONE",
--            dark_sidebar = true,
--            dark_float = true,
--            highlight_linenumber = true,
--            sidebars = {
--                "qf",
--                "vista_kind",
--                "terminal",
--                "packer",
--            },
--            colors = {
--                bg0 = "#16181d",
--                bg1 = "#16181d",
--                bg_highlight = "#2e3138",
--                bg_visual = "#2e3138",
--                black0 = "#20232A",
--                blue0 = "#9933ff",
--                blue1 = "#6600cc",
--                cyan0 = "#c266ff",
--                fg0 = "#abb2bf",
--                fg_dark = "#798294",
--                fg_gutter = "#16181d",
--                fg_light = "#adbac7",
--                green0 = "#98c379",
--                orange0 = "#e59b4e",
--                orange1 = "#d19a66",
--                purple0 = "#c678dd",
--                red0 = "#66cc66",
--                red1 = "#339933",
--                red2 = "#206020",
--                yellow0 = "#ebd09c",
--                yellow1 = "#e5c07b",
--                dev_icons = {
--                    blue = "#a074c4",
--                    green0 = "#8dc149",
--                    yellow = "#cbcb41",
--                    orange = "#e37933",
--                    red = "#cc3e44",
--                    purple = "#a074c4",
--                    pink = "#f55385",
--                    gray = "#4d5a5e",
--                },
--            },
--        })
--        vim.cmd("colorscheme onedark")
--    end
--}
