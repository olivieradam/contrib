### Lists of source files, included by Makefiles

AROS_STATE_TRACKER_SOURCES = \
            state_trackers/aros/arosmesa_api \
            
AROS_WINSYS_SOURCES = \
            winsys/aros/arosmesa_winsys \
            winsys/aros/arosmesa_softpipe \

GALLIUM_AUXILIARY_SOURCES = \
            auxiliary/util/u_debug \
            auxiliary/util/u_debug_symbol \
            auxiliary/util/u_debug_stack \
            auxiliary/util/u_blit \
            auxiliary/util/u_cache \
            auxiliary/util/u_draw_quad \
            auxiliary/util/u_gen_mipmap \
            auxiliary/util/u_handle_table \
            auxiliary/util/u_hash_table \
            auxiliary/util/u_hash \
            auxiliary/util/u_keymap \
            auxiliary/util/u_linear \
            auxiliary/util/u_mm \
            auxiliary/util/u_rect \
            auxiliary/util/u_simple_shaders \
            auxiliary/util/u_snprintf \
            auxiliary/util/u_stream_stdc \
            auxiliary/util/u_stream_wd \
            auxiliary/util/u_surface \
            auxiliary/util/u_tile \
            auxiliary/util/u_timed_winsys \
            auxiliary/util/u_upload_mgr \
            auxiliary/util/u_simple_screen \
            auxiliary/draw/draw_context \
            auxiliary/draw/draw_pipe \
            auxiliary/draw/draw_pipe_aaline \
            auxiliary/draw/draw_pipe_aapoint \
            auxiliary/draw/draw_pipe_cull \
            auxiliary/draw/draw_pipe_flatshade \
            auxiliary/draw/draw_pipe_offset \
            auxiliary/draw/draw_pipe_pstipple \
            auxiliary/draw/draw_pipe_stipple \
            auxiliary/draw/draw_pipe_twoside \
            auxiliary/draw/draw_pipe_unfilled \
            auxiliary/draw/draw_pipe_util \
            auxiliary/draw/draw_pipe_validate \
            auxiliary/draw/draw_pipe_vbuf \
            auxiliary/draw/draw_pipe_wide_line \
            auxiliary/draw/draw_pipe_wide_point \
            auxiliary/draw/draw_pt \
            auxiliary/draw/draw_pt_elts \
            auxiliary/draw/draw_pt_emit \
            auxiliary/draw/draw_pt_fetch \
            auxiliary/draw/draw_pt_fetch_emit \
            auxiliary/draw/draw_pt_fetch_shade_emit \
            auxiliary/draw/draw_pt_fetch_shade_pipeline \
            auxiliary/draw/draw_pt_post_vs \
            auxiliary/draw/draw_pt_util \
            auxiliary/draw/draw_pt_varray \
            auxiliary/draw/draw_pt_vcache \
            auxiliary/draw/draw_vertex \
            auxiliary/draw/draw_vs \
            auxiliary/draw/draw_vs_varient \
            auxiliary/draw/draw_vs_aos \
            auxiliary/draw/draw_vs_aos_io \
            auxiliary/draw/draw_vs_aos_machine \
            auxiliary/draw/draw_vs_exec \
            auxiliary/draw/draw_vs_llvm \
            auxiliary/draw/draw_vs_ppc  \
            auxiliary/draw/draw_vs_sse  \
            auxiliary/tgsi/tgsi_sanity \
            auxiliary/tgsi/tgsi_build \
            auxiliary/tgsi/tgsi_dump \
            auxiliary/tgsi/tgsi_exec \
            auxiliary/tgsi/tgsi_info \
            auxiliary/tgsi/tgsi_iterate \
            auxiliary/tgsi/tgsi_parse \
            auxiliary/tgsi/tgsi_ppc \
            auxiliary/tgsi/tgsi_scan \
            auxiliary/tgsi/tgsi_sse2 \
            auxiliary/tgsi/tgsi_text \
            auxiliary/tgsi/tgsi_transform \
            auxiliary/tgsi/tgsi_util \
            auxiliary/rtasm/rtasm_cpu \
            auxiliary/rtasm/rtasm_execmem \
            auxiliary/rtasm/rtasm_x86sse \
            auxiliary/rtasm/rtasm_ppc \
            auxiliary/rtasm/rtasm_ppc_spe \
            auxiliary/translate/translate_generic \
            auxiliary/translate/translate_sse \
            auxiliary/translate/translate \
            auxiliary/translate/translate_cache \
            auxiliary/cso_cache/cso_context \
            auxiliary/cso_cache/cso_cache \
            auxiliary/cso_cache/cso_hash \
            auxiliary/draw/draw_pipe_clip \
            auxiliary/util/u_math \
            auxiliary/util/u_time \

#FIXME: Not all auxiliary modules added yet

GALLIUM_SOFTPIPE_SOURCES = \
            drivers/softpipe/sp_fs_exec \
            drivers/softpipe/sp_fs_sse \
            drivers/softpipe/sp_fs_llvm \
            drivers/softpipe/sp_clear \
            drivers/softpipe/sp_flush \
            drivers/softpipe/sp_query \
            drivers/softpipe/sp_context \
            drivers/softpipe/sp_draw_arrays \
            drivers/softpipe/sp_prim_setup \
            drivers/softpipe/sp_prim_vbuf \
            drivers/softpipe/sp_quad_pipe \
            drivers/softpipe/sp_quad_alpha_test \
            drivers/softpipe/sp_quad_blend \
            drivers/softpipe/sp_quad_colormask \
            drivers/softpipe/sp_quad_coverage \
            drivers/softpipe/sp_quad_depth_test \
            drivers/softpipe/sp_quad_earlyz \
            drivers/softpipe/sp_quad_fs \
            drivers/softpipe/sp_quad_occlusion \
            drivers/softpipe/sp_quad_output \
            drivers/softpipe/sp_quad_stencil \
            drivers/softpipe/sp_quad_stipple \
            drivers/softpipe/sp_screen \
            drivers/softpipe/sp_setup \
            drivers/softpipe/sp_state_blend \
            drivers/softpipe/sp_state_clip \
            drivers/softpipe/sp_state_derived \
            drivers/softpipe/sp_state_fs \
            drivers/softpipe/sp_state_sampler \
            drivers/softpipe/sp_state_rasterizer \
            drivers/softpipe/sp_state_surface \
            drivers/softpipe/sp_state_vertex \
            drivers/softpipe/sp_texture \
            drivers/softpipe/sp_tex_sample \
            drivers/softpipe/sp_tile_cache \
            drivers/softpipe/sp_surface 

AROS_GALLIUM_SOURCES = \
            $(AROS_STATE_TRACKER_SOURCES) \
            $(AROS_WINSYS_SOURCES) \
            $(GALLIUM_SOFTPIPE_SOURCES) \
            $(GALLIUM_AUXILIARY_SOURCES) \