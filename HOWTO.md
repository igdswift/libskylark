libskylark Development Procedures
=================================

This document summarizes some practices around contributions to this
library. These instructions don't come with a warranty yet, so please
feel free to update it to mirror reality.

# Releasing New Versions of the Library

Congratulations, you've decided to release a new version of libskylark.

0. Branch and tag a new release. Tag the release version:

    ```shell
    # Produces most recent tag (e.g., v0.29)
    git describe --abbrev=0 --tags
    # Increment that value, create a new one (e.g, v0.30), and push
    git tag -a INCREMENTED_TAG
    git push upstream INCREMENTED_TAG
    ```

1. Add to RELEASE_NOTES.md and update the CHANGELOG details with `make
   release`. Submit a pull request. This requires
   [github-changelog-generator](https://github.com/skywinder/github-changelog-generator),
   and a CHANGELOG_GITHUB_TOKEN in your PATH if you don't already have
   them.

3. Create a release on
   [GitHub](https://github.com/swift-nav/libskylark/releases) and add
   the RELEASE_NOTES.md.

5. If needed, announce release to the
   [forum](https://groups.google.com/forum/#!forum/swiftnav-discuss).

6. Releases are not only never perfect, they never really end. Please
   pay special attention to any downstream projects or users that may
   have issues or regressions as a consequence of the release version.

# Contributions

This library is developed internally by Swift Navigation. We welcome
Github issues and pull requests, as well as discussions of potential
problems and enhancement suggestions on the
[forum](https://groups.google.com/forum/#!forum/swiftnav-discuss).
