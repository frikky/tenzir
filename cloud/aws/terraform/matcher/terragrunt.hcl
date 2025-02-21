include "root" {
  path = find_in_parent_folders("terragrunt.${get_env("TF_STATE_BACKEND")}.hcl")
}

# Core 1 is required for image deployment
dependency "core_1" {
  config_path = "../core-1"
}
dependency "core_2" {
  config_path = "../core-2"

  mock_outputs = {
    fargate_task_execution_role_arn = "arn:aws:iam:::role/temporary-dummy-arn"
    fargate_cluster_name            = "dummy_name"
    tenzir_server_hostname            = "dummy.local"
    tenzir_subnet_id                  = "dummy_id"
    tenzir_client_security_group_id   = "dummy_id"
  }
}

locals {
  region_name = get_env("TENZIR_AWS_REGION")
}

terraform {
  before_hook "deploy_images" {
    commands = ["apply"]
    execute = ["/bin/bash", "-c", <<EOT
../../tenzir-cloud docker-login \
                 build-images --step=matcher \
                 push-images --step=matcher && \
../../tenzir-cloud print-image-vars --step=matcher > images.generated.tfvars
EOT
    ]
  }

  extra_arguments "image_vars" {
    commands  = ["apply"]
    arguments = ["-var-file=${get_terragrunt_dir()}/images.generated.tfvars"]
  }

}

inputs = {
  region_name                     = local.region_name
  matcher_client_image            = "dummy_overriden_by_before_hook"
  fargate_task_execution_role_arn = dependency.core_2.outputs.fargate_task_execution_role_arn
  tenzir_server_hostname            = dependency.core_2.outputs.tenzir_server_hostname
  fargate_cluster_name            = dependency.core_2.outputs.fargate_cluster_name
  tenzir_subnet_id                  = dependency.core_2.outputs.tenzir_subnet_id
  tenzir_client_security_group_id   = dependency.core_2.outputs.tenzir_client_security_group_id
}
