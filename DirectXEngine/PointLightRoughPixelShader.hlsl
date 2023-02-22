Texture2D TextureColor: register(t0);
sampler TextureColorSampler: register(s0);

Texture2D Normal: register(t1);
sampler NormalSampler: register(s1);


struct PS_INPUT
{
	float4 position: SV_POSITION;
	float2 texcoord: TEXCOORD0;
	float3 normal: NORMAL0;
	float3 world_pos: TEXCOORD1;
	row_major float3x3 tbn: TEXCOORD2;
};

cbuffer constant: register(b0)
{
	row_major float4x4 m_world;
	row_major float4x4 m_view;
	row_major float4x4 m_proj;
	float4 m_light_direction;
	float4 m_camera_position;
	float4 m_light_position;
	float m_light_radius;
	float m_time;
};

float4 main(PS_INPUT input) : SV_TARGET
{
	float4 tex_color = TextureColor.Sample(TextureColorSampler, float2(input.texcoord.x,1.0 - input.texcoord.y));
	float4 normal = Normal.Sample(NormalSampler, float2(input.texcoord.x, 1.0 - input.texcoord.y));

	normal.xyz = (normal.xyz * 2.0) - 1.0;
	normal.xyz = mul(normal.xyz, input.tbn);

	float dot_nl = dot(m_light_direction.xyz, input.tbn[2]);

	//Phong Light Model:
	//AMBIENT LIGHT
	float constantAmbient = 5;
	float3 ambientColor = float3(0.09, 0.082, 0.082);
	ambientColor *= (tex_color.rgb);

	float3 ambient_light = constantAmbient * ambientColor;

	//DIFFUSE LIGHT
	float constantDiffuse = 0.7;
	float3 light_dir = normalize(m_light_position.xyz - input.world_pos.xyz);
	float distance_light_object = length(m_light_position.xyz - input.world_pos.xyz);

	float fade_area = max(0, distance_light_object - m_light_radius);

	float constant_func = 1.0;
	float linear_func = 1.0;
	float quadratic_func = 1.0;

	float attenuation = constant_func + linear_func * fade_area + quadratic_func * fade_area * fade_area;

	float amount_diffuse_light = max(0, dot(light_dir.xyz, normal));
	float3 diffuseColor = float3(1, 1, 1);
	diffuseColor *= (tex_color.rgb);

	float3 diffuse_light = (constantDiffuse * diffuseColor * amount_diffuse_light) / attenuation;

	//SPECULAR LIGHT
	float constantSpecular = 0;
	float3 direction_to_camera = normalize(input.world_pos.xyz - m_camera_position.xyz);
	float3 specularColor = float3(1.0, 1.0, 1.0);
	float3 reflected_light = reflect(light_dir.xyz, normal);
	float shininess = 30.0;
	float amount_specular_light = pow(max(0.0, dot(reflected_light, direction_to_camera)), shininess);

	float3 specular_light = (constantSpecular * amount_specular_light * specularColor) / attenuation;

	//FINAL LIGHT
	float3 final_light = ambient_light + diffuse_light + specular_light;

	return float4(final_light, 1.0);

}