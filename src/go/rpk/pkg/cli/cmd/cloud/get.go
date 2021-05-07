// Copyright 2021 Vectorized, Inc.
//
// Use of this software is governed by the Business Source License
// included in the file licenses/BSL.md
//
// As of the Change Date specified in that file, in accordance with
// the Business Source License, use of this software will be governed
// by the Apache License, Version 2.0

package cloud

import (
	"github.com/spf13/afero"
	"github.com/spf13/cobra"
)

func NewGetCommand(fs afero.Fs) *cobra.Command {
	command := &cobra.Command{
		Use:    "get",
		Short:  "Get resource from Vectorized cloud",
		Hidden: true,
	}

	command.AddCommand(NewNamespacesCommand(fs))
	command.AddCommand(NewClustersCommand(fs))

	return command
}
