Texture2D Texture: register(t0);
sampler TextureSampler: register(s0);

struct PS_INPUT
{
	float4 position: SV_POSITION;
	float2 texcoord: TEXCOORD0;
	float3 normal: TEXCOORD1;
	float3 direction_to_camera: TEXCOORD2;

	//float3 color: COLOR;
	//float3 color1: COLOR1;
};

cbuffer constant: register(b0)
{
	row_major float4x4 m_world;
	row_major float4x4 m_view;
	row_major float4x4 m_proj;
	float4 m_light_direction;
	//unsigned int m_time;
};

float4 main(PS_INPUT input) : SV_TARGET
{
	//Phong Light Model:
	//AMBIENT LIGHT
	float ka = 0.1;
	float3 ia = float3(1.0, 1.0, 1.0);

	float3 ambient_light = ka * ia;

	//DIFFUSE LIGHT
	float kd = 0.7;
	float3 id = float3(1.0, 1.0, 1.0);
	float amount_diffuse_light = max(0.0, dot(m_light_direction.xyz, input.normal));

	float3 diffuse_light = kd * amount_diffuse_light * id;

	//SPECULAR LIGHT
	float ks = 1.0;
	float3 is = float3(1.0, 1.0, 1.0);
	float3 reflected_light = reflect(m_light_direction.xyz, input.normal);
	float shininess = 50.0;
	float amount_specular_light = pow(max(0.0, dot(reflected_light, input.direction_to_camera)), shininess);

	float3 specular_light = ks * amount_specular_light * is;


	float3 final_light = ambient_light + diffuse_light + specular_light;

	return float4(final_light,1.0);

	//For the Cube:
	/*return float4(lerp(input.color, input.color1, (float)((sin((float)(m_time / (float)500.0f)) + 1.0f) / 2.0f)),1.0f);*/

	//For the Teapot:
	//return Texture.Sample(TextureSampler,input.texcoord*0.5);
}