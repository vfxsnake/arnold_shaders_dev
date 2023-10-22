#include <ai.h>

AI_SHADER_NODE_EXPORT_METHODS(SimpleMethods);

enum SimpleParams { p_color };

node_parameters
{
   AiParameterRGB("color", 0.7f, 0.7f, 0.7f);
}

node_initialize
{
}

node_update
{
}

node_finish
{
}

shader_evaluate
{
   AtVector n = sg->N;
   AtRGB weight = AiShaderEvalParamRGB(p_color);
   AtBSDF* bsdf =  AiOrenNayarBSDF(sg, weight,n);
   // sg->out.CLOSURE() = AiLightsIntegrateShadowMatte(sg);
   sg->out.CLOSURE() = bsdf;
}

node_loader
{
   if (i > 0)
      return false;
   node->methods     = SimpleMethods;
   node->output_type = AI_TYPE_CLOSURE;
   node->name        = "simple";
   node->node_type   = AI_NODE_SHADER;
   strcpy(node->version, AI_VERSION);
   return true;
} 