uniform sampler2D u_texture;

varying vec3 v_norm;
varying vec3 v_pos;
varying vec2 v_tex;

void main() {
	vec4 texc = texture2D(u_texture, vec2(v_tex.x, 1.0-v_tex.y));
	vec3 light_pos = vec3(0.0,-5.0,-5.0);
	vec3 light_dir = normalize(light_pos - v_pos);
	vec3 light_e = normalize(-v_pos);
	vec3 light_r = -reflect(light_dir, light_e);
	vec3 spec_color = vec3(1.0, 1.0, 1.0) * pow(max(dot(light_e, light_r), 0.0),4.0);
	float ndotl = max(dot(v_norm, light_dir), 0.0);

	
	gl_FragColor.a = 1.0;
	vec3 light_col = vec3(0.5,0.0,0.0);
	gl_FragColor.rgb =  mix(v_norm,  texc.rgb * (ndotl+0.1) + ndotl * light_col, 0.8) +spec_color;
	
	
	
	
	
//	gl_FragColor.rgb = v_norm * 0.3 + spec_color + texc.rgb + vec3(1.0,0.3,0.1) * ndotl;
//	gl_FragColor.rgb = spec_color + texc.rgb + mix( light_col * ndotl, v_norm, 0.1);
	//gl_FragColor.rgb = spec_color;
	//gl_FragColor.rgb = vec3(1.0, 0.0, 0.0) * ndotl;
//	gl_FragColor.rgb = v_norm;
}