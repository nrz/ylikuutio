### Ontology
The ontological hierarchy of Ylikuutio is based on composition.

## Entity
Each ontological class inherits [`yli::ontology::Entity`](../code/ylikuutio/ontology/entity.hpp) either directly or indirectly.
See [class_diagram.tex](class_diagram.tex) for a partial class diagram. TODO: update the class diagram!
Inheriting [`yli::ontology::Entity`](../code/ylikuutio/ontology/entity.hpp) enables the use of virtual functions common for all ontological Entities.

## Universe and EntityFactory
The recommended way to create Entities in a game or simulation is to first create [`yli::ontology::Universe`](../code/ylikuutio/ontology/universe.hpp)
and then get a [`yli::ontology::EntityFactory*`](../code/ylikuutio/ontology/entity_factory.hpp) pointer using `Universe::get_entity_factory` and then
create all other Entities using the member functions of that [`EntityFactory`](../code/ylikuutio/ontology/entity_factory.hpp).

There is no support for multiple simultaneous [`Universe`](../code/ylikuutio/ontology/universe.hpp) Entities. Do not create more than 1 `Universe`!

## Ontological hierarchy
All Entities of the ontological hierarchy form a tree with [`Universe`](../code/ylikuutio/ontology/universe.hpp) as the top node. Therefore every [`Entity`](../code/ylikuutio/ontology/entity.hpp) must be given a parent upon creation.

## GenericParentModule and ChildModule
Many parent-child-relationships are similar. Therefore some 'module' classes have been created to avoid writing the same binding and unbinding etc. code again and again. [`GenericParentModule`](../code/ylikuutio/ontology/generic_parent_module.hpp) provides 'parenting' functionality and [`ChildModule`](../code/ylikuutio/ontology/child_module.hpp) provides 'childing' functionality. `GenericParentModule` can be inherited to create some specialized module for some special 'parenting' needs, see [`ParentOfPipelinesModule`](../code/ylikuutio/ontology/parent_of_pipelines_module.hpp) for an example.

## Ecosystem and Scene
[`Universe`](../code/ylikuutio/ontology/universe.hpp) must be created as the first [`Entity`](../code/ylikuutio/ontology/entity.hpp). After creation of the `Universe`, 2 `Entity` classes of particular interest can be created, among others to be discussed later: [`Ecosystem`](../code/ylikuutio/ontology/ecosystem.hpp) and [`Scene`](../code/ylikuutio/ontology/scene.hpp). `Ecosystem` is basically an owner of collection of Entities, that's all it is. `Scene` is also a collection of Entities (just like an `Ecosystem`, but it is also a place that can be rendered with the [`Movable`](../code/ylikuutio/ontology/movable.hpp) Entities residing in it.

## Movable
[`Movable`](../code/ylikuutio/ontology/movable.hpp) is an abstract class to be inherited by the classes that represent the actual types of different Movables. We'll get back to those a little bit later.

## Pipeline
To render anything else but 2D text we need a [`Pipeline`](../code/ylikuutio/ontology/pipeline.hpp). The information of vertex pipeline and fragment pipeline need to be passed to the `Pipeline` constructor, which then works in RAII-style and makes everything ready regards to using the GLSL shaders later in the render call. `Pipeline` can be bound either to an [`Ecosystem`](../code/ylikuutio/ontology/ecosystem.hpp) or [`Scene`](../code/ylikuutio/ontology/scene.hpp).

## Material
The [`Movable`s](../code/ylikuutio/ontology/movable.hpp) often need a [`Material`](../code/ylikuutio/ontology/material.hpp). `Material` basically contains the texture but in the future it way have some shading features as well.

## Object and Species
The simplest kind of visible [`Movable`s](../code/ylikuutio/ontology/movable.hpp) are [`Object`](../code/ylikuutio/ontology/movable.hpp) instances. In order to render `Object`, we need `Pipeline`, `Material`, and [`Species`](../code/ylikuutio/ontology/species.hpp). `Species` contains the information about the 3D mesh of the model.

## Relationships
In our ontological hierarchy there are 2 kinds of relationships: parent-child relationships discussed already, and then there are master-apprentice relationships. In contrast to parent-child relationships, in master-apprentice relationships there is no ownership. An apprentice survives the deletion of its master and can continue its life although lacking the knowledge passed by the master.

## Rules of master-apprentice relationships
It should be noted that in master-apprentice relationships both parties need to reside in the same `Scene`, or at least one of them needs to reside in a `Ecosystem`. If either the master or the apprentice binds to a `Scene` different of the `Scene` the other party is bound to, then the master-apprentice relationship is broken. If the other party then binds to the same `Scene` or to an `Ecosystem` so that both are in the same `Scene` or at least one is in an `Ecosystem`, then the apprentice may bind to the master again to reinitiate the master-apprentice relationship.

## Rules of parent-child relationships
In parent-child relationships if the parent binds to a different `Scene` they take their children with them. On the other hand if the apprentice binds to a different `Scene`, that is, a new foster parent, the parent stays in the `Scene` where they reside already.

## In the future: messenger-recipient relationships?
In the future a third kind of relationship will probably be implemented, that is, the messenger-recipient relationship, which is the same as master-apprentice relationship, but without the requirement that both parties need to reside in the same `Scene` or at least one needs to reside in an `Ecosystem`. Messenger-recipient relationship is not implemented yet.

## An example of master-apprentice relationship: the Brain-Movable relationship
Let's sidetrack a bit to an actual simple case of master-apprentice relationship in Ylikuutio: the master-apprentice relationship between the [`Brain`](../code/ylikuutio/ontology/brain.hpp) and [`Movable`](../code/ylikuutio/ontology/movable.hpp). `Brain` as the 'master' provides the AI functionality for the `Movable`, so `Brain` makes the CPU-controlled `Movable`s behave according to the program written in that `Brain` instance (currently in C++, in the future in YliLisp as well). `Movable` here is the 'apprentice' and behaves according to what the program of its `Brain` says it to do. Note that any particular `Movable` instance has no exclusive relationship with the `Brain`: the same `Brain` may control numerous `Movable`s if so needed. On the other hand each `Movable` may be an 'apprentice' only to maximum of one `Brain` 'master' at any given moment: it would make no sense to receive contradicting commands from 2 or more different `Brain` masters. However, it is possible that in the future some kind of modular `Brain` instance may be written that owns several `Brain`s of its own and executes their commands to its `Movable` apprentices following some logic, but so far no such modular `Brain` has been implemented.

## How to create the Entities needed to render Objects
Now that we know about master-apprentice relationships as well, let's get back to the classes of the rendering pipeline:

There are many more classes as well, but now we have enough to wonder how the classes mentioned so far interact with each other. The simplest case is as follows:
1. We create the [`Universe`](../code/ylikuutio/ontology/universe.hpp)
2. We create the [`Scene`](../code/ylikuutio/ontology/scene.hpp) and make it a child of the [`Object`](../code/ylikuutio/ontology/object.hpp).
3. We create the [`Pipeline`](../code/ylikuutio/ontology/pipeline.hpp) and make it a child of the [`Scene`](../code/ylikuutio/ontology/scene.hpp).
3. We create the [`Material`](../code/ylikuutio/ontology/material.hpp) make it a child of the [`Scene`](../code/ylikuutio/ontology/scene.hpp), and an apprentice of the [`Pipeline`](../code/ylikuutio/ontology/pipeline.hpp).
4. We create the [`Species`](../code/ylikuutio/ontology/species.hpp) and make it a child of the [`Scene`](../code/ylikuutio/ontology/scene.hpp), and an apprentice of the [`Material`](../code/ylikuutio/ontology/material.hpp).
5. We create the [`Object`](../code/ylikuutio/ontology/object.hpp) and make it a child of the [`Scene`](../code/ylikuutio/ontology/scene.hpp), and an apprentice of the [`Species`](../code/ylikuutio/ontology/species.hpp).

## Rendering of Objects
Then upon rendering we do the following:
1. We render the currently active [`Scene`](../code/ylikuutio/ontology/scene.hpp), and render all its [`Pipeline`s](../code/ylikuutio/ontology/pipeline.hpp).
2. Upon rendering any given [`Pipeline`](../code/ylikuutio/ontology/pipeline.hpp), we render all its [`Material`s](../code/ylikuutio/ontology/material.hpp).
3. Upon rendering any given [`Material`](../code/ylikuutio/ontology/material.hpp), we render all its [`Species`](../code/ylikuutio/ontology/species.hpp).
4. Upon rendering any given [`Species`](../code/ylikuutio/ontology/species.hpp), we render all its [`Object`s](../code/ylikuutio/ontology/object.hpp).

## How Ecosystems work in rendering
Things are more complicated when one or more [`Ecosystem`s](../code/ylikuutio/ontology/ecosystem.hpp) are used. Several different types of Entities can be bound to an `Ecosystem`. In that case in the rendering pipeline only such Entities are chosen that resides in the [`Scene`](../code/ylikuutio/ontology/scene.hpp) chosen for rendering, or in an `Ecosystem`, and the information about the chosen `Scene` gets passed down in rendering pipeline to do this selection for every [`Entity`](../code/ylikuutio/ontology/entity.hpp) that gets processed in some way in the rendering pipeline.

## Symbiosis Entities, Holobionts, and classes related to them
Let's discuss a little bit about [`Symbiosis`](../code/ylikuutio/ontology/symbiosis.hpp) Entities. `Symbiosis` are all about coexistence of different lifeforms, in our case about the coexistence of [`SymbiontMaterial`](../code/ylikuutio/ontology/symbiont_material.hpp) and [`SymbiontSpecies`](../code/ylikuutio/ontology/symbiont_material.hpp) Entities. `SymbiontMaterial`s work similarly to `Material`s and provide the textures. `SymbiontSpecies`s work similarly to `Species` and provide the 3D meshes. Then, the `Symbiosis` may have [`Holobiont`](../code/ylikuutio/ontology/holobiont.hpp) Entities as their apprentices. `Holobiont`s are composite organisms, so each `Holobiont` instance is an actualized 3D model of the `Symbiosis`, using the textures defined by the `SymbiontMaterial`s and the meshes defined by the `SymbiontSpecies`. Each mesh of the `Holobiont` is a [`Biont`](../code/ylikuutio/ontology/biont.hpp) Entity and the `Biont`s of any `Holobiont` are created upon creation of the `Holobiont` itself.

For more information about holobionts, check Wikipedia:
* https://en.wikipedia.org/wiki/Holobiont

## How to create the Entities needed to render Holobionts
Let's see how we create [`Symbiosis`](../code/ylikuutio/ontology/symbiosis.hpp) and [`Holobiont`](../code/ylikuutio/ontology/holobiont.hpp) Entities:
1. We create the [`Universe`](../code/ylikuutio/ontology/universe.hpp)
2. We create the [`Scene`](../code/ylikuutio/ontology/scene.hpp) and make it a child of the `Universe`.
3. We create the [`Pipeline`](../code/ylikuutio/ontology/pipeline.hpp) and make it a child of the `Scene`.
4. We create the [`Symbiosis`](../code/ylikuutio/ontology/symbiosis.hpp) make it a child of the `Scene`, and an apprentice of the `Pipeline`.
5. We create the [`Holobiont`](../code/ylikuutio/ontology/holobiont.hpp) and make it a child of the `Scene`, and an apprentice of the `Symbiosis`.

Regarding [`Symbiosis`](../code/ylikuutio/ontology/symbiosis.hpp) Entities, [`SymbiontMaterial`](../code/ylikuutio/ontology/symbiont_material.hpp) and [`SymbiontSpecies`](../code/ylikuutio/ontology/symbiont_material.hpp) are usually implementation details that you don't need to worry about, but they are nontheless and and are counted as children of the `Symbiosis`. Same applies to [`Biont`s](../code/ylikuutio/ontology/biont.hpp) of any [`Holobiont`](../code/ylikuutio/ontology/holobiont.hpp), though in the future there will probably be support for manipulating individual `Biont`s. Manipulating individual `Biont`s is not implemented yet.

## Rendering of Holobionts
The rendering of the [`Holobiont`s](../code/ylikuutio/ontology/holobiont.hpp) happens similarly to the [`Object`s](../code/ylikuutio/ontology/movable.hpp):
1. We render the currently active [`Scene`](../code/ylikuutio/ontology/scene.hpp), and render all its [`Pipeline`s](../code/ylikuutio/ontology/pipeline.hpp).
2. Upon rendering any given [`Pipeline`](../code/ylikuutio/ontology/pipeline.hpp), we render all its [`Symbiosis`](../code/ylikuutio/ontology/symbiosis.hpp) Entities.
3. Upon rendering any given [`Symbiosis`](../code/ylikuutio/ontology/symbiosis.hpp), we render all its [`Holobiont`s](../code/ylikuutio/ontology/holobiont.hpp).
4. Upon rendering any given [`Holobiont`](../code/ylikuutio/ontology/holobiont.hpp), we render all its `Biont`s.

## TODO
* Document `Font2D` and `Text2D` rendering!
* Document `EntityFactory`!
* Implement and document manipulating individual `Biont`s!
* Implement and document `VectorFont` and Text3D` rendering!
* Implement and document `PipelineSymbiosis` Entities!
* Implement and document `ShapeshifterTransformation`, `ShapeshifterSequence`, `ShapeshifterForm`!
