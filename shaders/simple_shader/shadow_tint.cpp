#include <ai.h>

AI_SHADER_NODE_EXPORT_METHODS(ShadowTintMethods)

enum DiffuseParams {
   p_color,
   p_shadow_tint,
   p_shadow_weight
};

node_parameters
{
   AiParameterRGB("base_color", 1.0f, 1.0f, 1.0f);
   AiParameterRGB("shadow_tint", 0.8f, 0.8f, 0.8f);
   AiParameterFlt("shadow_weight", 1.0);
}

node_initialize
{
   // create 3D sampler for BSDF sampling
   const int seed = 3158863998;
   const int nsamples = 4;
   const int ndim = 3;
   AtSampler *sampler = AiSampler(seed, nsamples, ndim);
   AiNodeSetLocalData(node, sampler);
}

node_update
{
}

node_finish
{
   AtSampler *sampler = (AtSampler*)AiNodeGetLocalData(node);
   AiSamplerDestroy(sampler);
}

static float PowerHeuristic(float pdf_a, float pdf_b)
{
   return AiSqr(pdf_a) / (AiSqr(pdf_a) + AiSqr(pdf_b));
}


shader_evaluate
{
   // early out for shadow rays and black
   if (sg->Rt & AI_RAY_SHADOW)
      return;

   AtRGB base_color = AiShaderEvalParamRGB(p_color);
   AtRGB shadow_tint = AiShaderEvalParamRGB(p_shadow_tint) * base_color;

   if (AiColorIsSmall(base_color))
      return;

   // create and integrate BSDF
   AtBSDF *bsdf = AiOrenNayarBSDF(sg, base_color, sg->Nf);
   AtRGB shadow_mask = AiLightsIntegrateShadowMatte(sg, bsdf) * AiShaderEvalParamFlt(p_shadow_weight);
   sg->out.RGB() = shadow_mask * shadow_tint + base_color * (1 - shadow_mask);
   
}

node_loader
{
   if (i > 0)
      return false;
   node->methods     = ShadowTintMethods;
   node->output_type = AI_TYPE_RGB;
   node->name        = "csShadowTint";
   node->node_type   = AI_NODE_SHADER;
   strcpy(node->version, AI_VERSION);
   return true;
} 