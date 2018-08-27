﻿Shader "PBR"
{
	Properties
	{
        _MainTex ("MainTex", 2D) = "white" {}
        [NoScaleOffset] _Normal ("Normal", 2D) = "bump" {}
        [NoScaleOffset] _MetallicSmoothness ("MetallicSmoothness (RA)", 2D) = "white" {}
		_Metallic ("Metallic", Range(0, 1)) = 0.0
        _Smoothness ("Smoothness", Range(0, 1)) = 0.5
        [NoScaleOffset] _Occlusion ("Occlusion", 2D) = "white" {}
        _OcclusionStrength ("OcclusionStrength", Range(0, 1)) = 1.0
        [NoScaleOffset] _Emission ("Emission", 2D) = "white" {}
        _EmissionColor ("EmissionColor", Color) = (0, 0, 0, 1)

        [NoScaleOffset] _Environment("Environment", Cube) = "" {}
        _Ambient("Ambient", Color) = (0, 0, 0, 1)
        _LightDir("LightDir", Vector) = (0, 0, 1, 0)
        _LightColor("LightColor", Color) = (1, 1, 1, 1)
	}
	SubShader
	{
		Pass
		{
            Tags{ "LightMode" = "ForwardBase" }

			CGPROGRAM
			#pragma vertex vert
			#pragma fragment frag
            #define surface_input surf_in
            #define surface surf

			#include "UnityCG.cginc"

            struct Input
            {
                float2 uv;
            };

            #include "PBR.cginc"

            float3 blend_rnm(float3 n1, float3 n2)
            {
                n1.z += 1;
                n2.xy = -n2.xy;

                return n1 * dot(n1, n2) / n1.z - n2;
            }

            void surf_in(v2f i, inout Input IN)
            {
                IN.uv = i.uv.xy * _MainTex_ST.xy + _MainTex_ST.zw;
            }

            void surf(Input IN, inout SurfaceOutputStandard o)
            {
                fixed4 albedo = tex2D(_MainTex, IN.uv);

                float3 normal = UnpackNormal(tex2D(_Normal, IN.uv));
                half4 metallicSmoothness = tex2D(_MetallicSmoothness, IN.uv);
                half metallic = metallicSmoothness.r * _Metallic;
                half smoothness = metallicSmoothness.a * _Smoothness;
                half occlusion = lerp(1, tex2D(_Occlusion, IN.uv).g, _OcclusionStrength);
                half3 emission = tex2D(_Emission, IN.uv) * _EmissionColor;

                o.Albedo = albedo.rgb;
                o.Normal = normal;
                o.Metallic = metallic;
                o.Smoothness = smoothness;
                o.Occlusion = occlusion;
                o.Emission = emission;
                o.Alpha = albedo.a;
            }
			ENDCG
		}
	}
}