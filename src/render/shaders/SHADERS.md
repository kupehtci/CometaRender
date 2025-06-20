# Built-in Shaders

This document describes the shaders in `src/render/shaders` that are built-in within Cometa Render and their purpose in the rendering pipeline.


#### blinn_phong_shader.vert / blinn_phong_shader.frag
 Implements the classic Blinn-Phong lighting model for per-pixel lighting with support for multiple lights, shadow mapping, and material textures (diffuse, specular, emission). Used for most lit 3D objects.
- **Vertex:** Transforms vertices, computes world position, normal, and shadow coordinates.
- **Fragment:** Handles lighting, shadows, and material properties.



#### movement_blinn_phong_shader.vert
 Like `blinn_phong_shader.vert`, but animates the Y position of vertices in a wave pattern using a time uniform. Used for GPU-side animated objects.



#### light_shader.vert / light_shader.frag
 Renders light sources as visible objects (e.g., spheres for point lights). Minimal shading, usually just color.
- **Vertex:** Transforms light mesh vertices.
- **Fragment:** Outputs the light's color.



#### shadow_map.vert / shadow_map.frag
 Used for rendering the scene from the light's perspective to create a shadow map (depth map) for directional lights.
- **Vertex:** Transforms geometry into light space.
- **Fragment:** Empty; only depth is written.



#### point_shadow_map.vert / point_shadow_map.frag / point_shadow_map.geom
 Used for rendering shadow maps for point lights (omnidirectional shadows, cubemap).
- **Vertex:** Transforms geometry for each face of the cubemap.
- **Geometry:** Emits geometry for all 6 cubemap faces.
- **Fragment:** Writes depth from the light to the fragment.



#### basic_shader.vert / basic_shader.frag
Minimal shaders for unlit geometry, debugging, or simple color rendering.


#### debug_shader.vert / debug_shader.frag
 Used for visual debugging, e.g., rendering normals, wireframes, or other debug visualizations.


#### material_shader.frag
 Handles material-specific fragment shading, possibly for UI or special effects.


#### fragment_shader.frag / fragment_shader_uniform.frag
 Generic or test fragment shaders, possibly for experiments or fallback rendering.


#### light_map_shader.vert / light_map_shader.frag
 For rendering with lightmaps (precomputed lighting), if used in the project.


#### vertex_shader.vert / vertex_shader_coords.vert / vertex_shader_coords_normals.vert
 Minimal or test vertex shaders for various attribute layouts (positions, coords, normals).
