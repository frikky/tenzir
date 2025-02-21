# Deploy a node

A *node* is a managed service for pipelines and storage.

## Install a node

Start at [app.tenzir.com](https://app.tenzir.com) and click *Add* in the nodes
pane. Then select your platform.

### Docker

We provide Docker images and a Docker Compose file for a container setup.
Install a node as follows:

1. Enter a name for your node and click the download button to obtain the
   `docker-compose.NODE.yaml` configuration file where `NODE` is the name you
   entered for your node.
2. Run
   ```bash
   docker compose -f docker-compose.NODE.yaml up
   ```

Edit the Docker Compose file and change [environment
variables](../../configuration.md#environment-variables) to adjust the
configuration.

### Linux

We offer a native deployment on various Linux distributions.
Install a node as follows:

1. Enter a name for your node and click the download button to obtain a
   `platform.yaml` configuration file.
2. Move the `platform.yaml` to `<sysconfdir>/tenzir/plugin/platform.yaml` so
   that the node can find it during startup where `<sysconfdir>` might be
   `/etc`. See the [configuration files
   documentation](../../configuration.md#configuration-files) for more options.
3. Run our installer to install a binary package on any Linux distribution:
   ```bash
   curl https://get.tenzir.app | sh
   ```

The installer script asks for confirmation before performing the installation.
If you prefer a manual installation you can also perform the installer steps
yourself.

import Tabs from '@theme/Tabs';
import TabItem from '@theme/TabItem';

<Tabs>
<TabItem value="debian" label="Debian">

Download the latest [Debian package][tenzir-debian-package] and install it via
`dpkg`:

```bash
dpkg -i tenzir-static-amd64-linux.deb
```

[tenzir-debian-package]: https://github.com/tenzir/tenzir/releases/latest/download/tenzir-static-amd64-linux.deb

</TabItem>
<TabItem value="nix" label="Nix">

Use our `flake.nix`:

```bash
nix run github:tenzir/tenzir/stable
```

Install Tenzir by adding `github:tenzir/tenzir/stable` to your flake inputs, or
use your preferred method to include third-party modules on classic NixOS.

</TabItem>
<TabItem value="any" label="Any">

Download a tarball with our [static binary][tenzir-tarball] for all Linux
distributions and unpack it into `/opt/tenzir`:

```bash
tar xzf tenzir-static-x86_64-linux.tar.gz -C /
```

[tenzir-tarball]: https://github.com/tenzir/tenzir/releases/latest/download/tenzir-static-x86_64-linux.tar.gz

We also offer prebuilt statically linked binaries for every Git commit to the
`main` branch.

```bash
curl -O https://storage.googleapis.com/tenzir-dist-public/packages/main/tarball/tenzir-static-main.gz
```

</TabItem>
</Tabs>

### macOS

Please use Docker [with
Rosetta](https://levelup.gitconnected.com/docker-on-apple-silicon-mac-how-to-run-x86-containers-with-rosetta-2-4a679913a0d5)
until we offer a native package.

## Start a node

:::info Implicit start with Docker
You can skip this step if you use [Docker](#docker) because `docker compose up`
already starts a node for you.
:::

Run the `tenzir-node` executable to start a node:

```bash
tenzir-node
```

```
      _____ _____ _   _ ________ ____
     |_   _| ____| \ | |__  /_ _|  _ \
       | | |  _| |  \| | / / | || |_) |
       | | | |___| |\  |/ /_ | ||  _ <
       |_| |_____|_| \_/____|___|_| \_\

          v4.0.0-rc6-0-gf193b51f1f
Visit https://app.tenzir.com to get started.
```

This will spawn a blocking process that listens by default on the TCP endpoint
`127.0.0.1:5158`. Select a different endpoint via `--endpoint`, e.g., bind to an
IPv6 address:

```bash
tenzir-node --endpoint=[::1]:42000
```

## Stop a node

There exist two ways stop a server:

1. Hit CTRL+C in the same TTY where you ran `tenzir-node`.
2. Send the process a SIGINT or SIGTERM signal, e.g., via
   `pkill -2 tenzir-node`.

Sending the process a SIGTERM is the same as hitting CTRL+C.

## Automate the deployment

Read our guides on automating the deployment of a node:

- [Systemd](systemd.md)
- [Ansible](ansible.md)
