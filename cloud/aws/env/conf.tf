locals {
  envs = {
    default = {
      # todo: pin release
      vast_server_image = "tenzir/vast:latest"
      vast_lambda_image = "tenzir/vast-lambda:latest"
    }
    test = {
      vast_server_image = "tenzir/vast:latest"
      vast_lambda_image = "tenzir/vast-lambda:latest"
    }
  }
  current_env = local.envs[terraform.workspace]
  module_name = "vast"
}

output "stage" {
  value = terraform.workspace
}

output "module_name" {
  value = local.module_name
}

output "vast_server_image" {
  value = local.current_env["vast_server_image"]
}

output "vast_lambda_image" {
  value = local.current_env["vast_lambda_image"]
}