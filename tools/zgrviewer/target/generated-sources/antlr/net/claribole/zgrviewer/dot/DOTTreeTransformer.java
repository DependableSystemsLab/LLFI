// $ANTLR 2.7.7 (20060906): "DOTTreeTransformer.g" -> "DOTTreeTransformer.java"$

package net.claribole.zgrviewer.dot;

import antlr.TreeParser;
import antlr.Token;
import antlr.collections.AST;
import antlr.RecognitionException;
import antlr.ANTLRException;
import antlr.NoViableAltException;
import antlr.MismatchedTokenException;
import antlr.SemanticException;
import antlr.collections.impl.BitSet;
import antlr.ASTPair;
import antlr.collections.impl.ASTArray;


public class DOTTreeTransformer extends antlr.TreeParser       implements DOTTreeTransformerTokenTypes
 {

	public String cleanAttribute(String value) {
		if(value.startsWith("\"") && value.endsWith("\""))
			return value.substring(1, value.length() - 1).trim();
		else return value;
	}
public DOTTreeTransformer() {
	tokenNames = _tokenNames;
}

	public final void graph(AST _t) throws RecognitionException {
		
		AST graph_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST graph_AST = null;
		
		try {      // for error handling
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case DIGRAPH:
			{
				AST __t2 = _t;
				AST tmp1_AST = null;
				AST tmp1_AST_in = null;
				tmp1_AST = astFactory.create((AST)_t);
				tmp1_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp1_AST);
				ASTPair __currentAST2 = currentAST.copy();
				currentAST.root = currentAST.child;
				currentAST.child = null;
				match(_t,DIGRAPH);
				_t = _t.getFirstChild();
				AST tmp2_AST = null;
				AST tmp2_AST_in = null;
				tmp2_AST = astFactory.create((AST)_t);
				tmp2_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp2_AST);
				match(_t,ID);
				_t = _t.getNextSibling();
				stmt_list(_t);
				_t = _retTree;
				astFactory.addASTChild(currentAST, returnAST);
				currentAST = __currentAST2;
				_t = __t2;
				_t = _t.getNextSibling();
				graph_AST = (AST)currentAST.root;
				break;
			}
			case GRAPH:
			{
				AST __t3 = _t;
				AST tmp3_AST = null;
				AST tmp3_AST_in = null;
				tmp3_AST = astFactory.create((AST)_t);
				tmp3_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp3_AST);
				ASTPair __currentAST3 = currentAST.copy();
				currentAST.root = currentAST.child;
				currentAST.child = null;
				match(_t,GRAPH);
				_t = _t.getFirstChild();
				AST tmp4_AST = null;
				AST tmp4_AST_in = null;
				tmp4_AST = astFactory.create((AST)_t);
				tmp4_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp4_AST);
				match(_t,ID);
				_t = _t.getNextSibling();
				stmt_list(_t);
				_t = _retTree;
				astFactory.addASTChild(currentAST, returnAST);
				currentAST = __currentAST3;
				_t = __t3;
				_t = _t.getNextSibling();
				graph_AST = (AST)currentAST.root;
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		returnAST = graph_AST;
		_retTree = _t;
	}
	
	public final void stmt_list(AST _t) throws RecognitionException {
		
		AST stmt_list_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST stmt_list_AST = null;
		
		try {      // for error handling
			AST __t5 = _t;
			AST tmp5_AST = null;
			AST tmp5_AST_in = null;
			tmp5_AST = astFactory.create((AST)_t);
			tmp5_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp5_AST);
			ASTPair __currentAST5 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,LCUR);
			_t = _t.getFirstChild();
			{
			_loop7:
			do {
				if (_t==null) _t=ASTNULL;
				if ((_tokenSet_0.member(_t.getType()))) {
					stmt(_t);
					_t = _retTree;
					astFactory.addASTChild(currentAST, returnAST);
				}
				else {
					break _loop7;
				}
				
			} while (true);
			}
			currentAST = __currentAST5;
			_t = __t5;
			_t = _t.getNextSibling();
			stmt_list_AST = (AST)currentAST.root;
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		returnAST = stmt_list_AST;
		_retTree = _t;
	}
	
	public final void stmt(AST _t) throws RecognitionException {
		
		AST stmt_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST stmt_AST = null;
		
		try {      // for error handling
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case SUBGRAPH:
			case ID:
			case LCUR:
			case LBR:
			case D_EDGE_OP:
			case ND_EDGE_OP:
			case COLON:
			{
				node_edge_subgraph_stmt(_t);
				_t = _retTree;
				astFactory.addASTChild(currentAST, returnAST);
				stmt_AST = (AST)currentAST.root;
				break;
			}
			case GRAPH:
			case NODE:
			case EDGE:
			{
				attr_stmt(_t);
				_t = _retTree;
				astFactory.addASTChild(currentAST, returnAST);
				stmt_AST = (AST)currentAST.root;
				break;
			}
			case EQUAL:
			{
				AST __t9 = _t;
				AST tmp6_AST = null;
				AST tmp6_AST_in = null;
				tmp6_AST = astFactory.create((AST)_t);
				tmp6_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp6_AST);
				ASTPair __currentAST9 = currentAST.copy();
				currentAST.root = currentAST.child;
				currentAST.child = null;
				match(_t,EQUAL);
				_t = _t.getFirstChild();
				AST tmp7_AST = null;
				AST tmp7_AST_in = null;
				tmp7_AST = astFactory.create((AST)_t);
				tmp7_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp7_AST);
				match(_t,ID);
				_t = _t.getNextSibling();
				AST tmp8_AST = null;
				AST tmp8_AST_in = null;
				tmp8_AST = astFactory.create((AST)_t);
				tmp8_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp8_AST);
				match(_t,ID);
				_t = _t.getNextSibling();
				currentAST = __currentAST9;
				_t = __t9;
				_t = _t.getNextSibling();
				stmt_AST = (AST)currentAST.root;
				break;
			}
			case LABEL:
			{
				AST __t10 = _t;
				AST tmp9_AST = null;
				AST tmp9_AST_in = null;
				tmp9_AST = astFactory.create((AST)_t);
				tmp9_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp9_AST);
				ASTPair __currentAST10 = currentAST.copy();
				currentAST.root = currentAST.child;
				currentAST.child = null;
				match(_t,LABEL);
				_t = _t.getFirstChild();
				AST tmp10_AST = null;
				AST tmp10_AST_in = null;
				tmp10_AST = astFactory.create((AST)_t);
				tmp10_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp10_AST);
				match(_t,ID);
				_t = _t.getNextSibling();
				currentAST = __currentAST10;
				_t = __t10;
				_t = _t.getNextSibling();
				stmt_AST = (AST)currentAST.root;
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		returnAST = stmt_AST;
		_retTree = _t;
	}
	
	public final void node_edge_subgraph_stmt(AST _t) throws RecognitionException {
		
		AST node_edge_subgraph_stmt_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST node_edge_subgraph_stmt_AST = null;
		AST n_AST = null;
		AST n = null;
		AST l_AST = null;
		AST l = null;
		
		try {      // for error handling
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case D_EDGE_OP:
			case ND_EDGE_OP:
			{
				edges(_t);
				_t = _retTree;
				astFactory.addASTChild(currentAST, returnAST);
				node_edge_subgraph_stmt_AST = (AST)currentAST.root;
				break;
			}
			case SUBGRAPH:
			case LCUR:
			{
				subgraph(_t);
				_t = _retTree;
				astFactory.addASTChild(currentAST, returnAST);
				node_edge_subgraph_stmt_AST = (AST)currentAST.root;
				break;
			}
			case ID:
			case COLON:
			{
				node_id(_t);
				_t = _retTree;
				astFactory.addASTChild(currentAST, returnAST);
				node_edge_subgraph_stmt_AST = (AST)currentAST.root;
				break;
			}
			case LBR:
			{
				boolean record = false;
				AST __t12 = _t;
				AST tmp11_AST = null;
				AST tmp11_AST_in = null;
				tmp11_AST = astFactory.create((AST)_t);
				tmp11_AST_in = (AST)_t;
				ASTPair __currentAST12 = currentAST.copy();
				currentAST.root = currentAST.child;
				currentAST.child = null;
				match(_t,LBR);
				_t = _t.getFirstChild();
				n = _t==ASTNULL ? null : (AST)_t;
				node_id(_t);
				_t = _retTree;
				n_AST = (AST)returnAST;
				l = _t==ASTNULL ? null : (AST)_t;
				record=a_list_node(_t);
				_t = _retTree;
				l_AST = (AST)returnAST;
				currentAST = __currentAST12;
				_t = __t12;
				_t = _t.getNextSibling();
				node_edge_subgraph_stmt_AST = (AST)currentAST.root;
				
							if(record) {
								node_edge_subgraph_stmt_AST = (AST)astFactory.make( (new ASTArray(3)).add(astFactory.create(RBR,"]")).add(n_AST).add(l_AST));
							}
							else {
								node_edge_subgraph_stmt_AST = (AST)astFactory.make( (new ASTArray(3)).add(astFactory.create(tmp11_AST)).add(n_AST).add(l_AST));
							}
						
				currentAST.root = node_edge_subgraph_stmt_AST;
				currentAST.child = node_edge_subgraph_stmt_AST!=null &&node_edge_subgraph_stmt_AST.getFirstChild()!=null ?
					node_edge_subgraph_stmt_AST.getFirstChild() : node_edge_subgraph_stmt_AST;
				currentAST.advanceChildToEnd();
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		returnAST = node_edge_subgraph_stmt_AST;
		_retTree = _t;
	}
	
	public final void attr_stmt(AST _t) throws RecognitionException {
		
		AST attr_stmt_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST attr_stmt_AST = null;
		
		try {      // for error handling
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case GRAPH:
			{
				AST __t33 = _t;
				AST tmp12_AST = null;
				AST tmp12_AST_in = null;
				tmp12_AST = astFactory.create((AST)_t);
				tmp12_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp12_AST);
				ASTPair __currentAST33 = currentAST.copy();
				currentAST.root = currentAST.child;
				currentAST.child = null;
				match(_t,GRAPH);
				_t = _t.getFirstChild();
				attr_list_graph(_t);
				_t = _retTree;
				astFactory.addASTChild(currentAST, returnAST);
				currentAST = __currentAST33;
				_t = __t33;
				_t = _t.getNextSibling();
				attr_stmt_AST = (AST)currentAST.root;
				break;
			}
			case NODE:
			{
				AST __t34 = _t;
				AST tmp13_AST = null;
				AST tmp13_AST_in = null;
				tmp13_AST = astFactory.create((AST)_t);
				tmp13_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp13_AST);
				ASTPair __currentAST34 = currentAST.copy();
				currentAST.root = currentAST.child;
				currentAST.child = null;
				match(_t,NODE);
				_t = _t.getFirstChild();
				attr_list_generic_node(_t);
				_t = _retTree;
				astFactory.addASTChild(currentAST, returnAST);
				currentAST = __currentAST34;
				_t = __t34;
				_t = _t.getNextSibling();
				attr_stmt_AST = (AST)currentAST.root;
				break;
			}
			case EDGE:
			{
				AST __t35 = _t;
				AST tmp14_AST = null;
				AST tmp14_AST_in = null;
				tmp14_AST = astFactory.create((AST)_t);
				tmp14_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp14_AST);
				ASTPair __currentAST35 = currentAST.copy();
				currentAST.root = currentAST.child;
				currentAST.child = null;
				match(_t,EDGE);
				_t = _t.getFirstChild();
				attr_list_generic_edge(_t);
				_t = _retTree;
				astFactory.addASTChild(currentAST, returnAST);
				currentAST = __currentAST35;
				_t = __t35;
				_t = _t.getNextSibling();
				attr_stmt_AST = (AST)currentAST.root;
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		returnAST = attr_stmt_AST;
		_retTree = _t;
	}
	
	public final void edges(AST _t) throws RecognitionException {
		
		AST edges_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST edges_AST = null;
		
		try {      // for error handling
			{
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case D_EDGE_OP:
			{
				AST __t15 = _t;
				AST tmp15_AST = null;
				AST tmp15_AST_in = null;
				tmp15_AST = astFactory.create((AST)_t);
				tmp15_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp15_AST);
				ASTPair __currentAST15 = currentAST.copy();
				currentAST.root = currentAST.child;
				currentAST.child = null;
				match(_t,D_EDGE_OP);
				_t = _t.getFirstChild();
				{
				if (_t==null) _t=ASTNULL;
				switch ( _t.getType()) {
				case D_EDGE_OP:
				case ND_EDGE_OP:
				{
					edges(_t);
					_t = _retTree;
					astFactory.addASTChild(currentAST, returnAST);
					break;
				}
				case ID:
				case COLON:
				{
					node_id(_t);
					_t = _retTree;
					astFactory.addASTChild(currentAST, returnAST);
					break;
				}
				default:
				{
					throw new NoViableAltException(_t);
				}
				}
				}
				node_id(_t);
				_t = _retTree;
				astFactory.addASTChild(currentAST, returnAST);
				{
				if (_t==null) _t=ASTNULL;
				switch ( _t.getType()) {
				case LBR:
				{
					attr_list_edge(_t);
					_t = _retTree;
					astFactory.addASTChild(currentAST, returnAST);
					break;
				}
				case 3:
				{
					break;
				}
				default:
				{
					throw new NoViableAltException(_t);
				}
				}
				}
				currentAST = __currentAST15;
				_t = __t15;
				_t = _t.getNextSibling();
				break;
			}
			case ND_EDGE_OP:
			{
				AST __t18 = _t;
				AST tmp16_AST = null;
				AST tmp16_AST_in = null;
				tmp16_AST = astFactory.create((AST)_t);
				tmp16_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp16_AST);
				ASTPair __currentAST18 = currentAST.copy();
				currentAST.root = currentAST.child;
				currentAST.child = null;
				match(_t,ND_EDGE_OP);
				_t = _t.getFirstChild();
				{
				if (_t==null) _t=ASTNULL;
				switch ( _t.getType()) {
				case D_EDGE_OP:
				case ND_EDGE_OP:
				{
					edges(_t);
					_t = _retTree;
					astFactory.addASTChild(currentAST, returnAST);
					break;
				}
				case ID:
				case COLON:
				{
					node_id(_t);
					_t = _retTree;
					astFactory.addASTChild(currentAST, returnAST);
					break;
				}
				default:
				{
					throw new NoViableAltException(_t);
				}
				}
				}
				node_id(_t);
				_t = _retTree;
				astFactory.addASTChild(currentAST, returnAST);
				{
				if (_t==null) _t=ASTNULL;
				switch ( _t.getType()) {
				case LBR:
				{
					attr_list_edge(_t);
					_t = _retTree;
					astFactory.addASTChild(currentAST, returnAST);
					break;
				}
				case 3:
				{
					break;
				}
				default:
				{
					throw new NoViableAltException(_t);
				}
				}
				}
				currentAST = __currentAST18;
				_t = __t18;
				_t = _t.getNextSibling();
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
			}
			edges_AST = (AST)currentAST.root;
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		returnAST = edges_AST;
		_retTree = _t;
	}
	
	public final void subgraph(AST _t) throws RecognitionException {
		
		AST subgraph_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST subgraph_AST = null;
		
		try {      // for error handling
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case SUBGRAPH:
			{
				AST __t29 = _t;
				AST tmp17_AST = null;
				AST tmp17_AST_in = null;
				tmp17_AST = astFactory.create((AST)_t);
				tmp17_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp17_AST);
				ASTPair __currentAST29 = currentAST.copy();
				currentAST.root = currentAST.child;
				currentAST.child = null;
				match(_t,SUBGRAPH);
				_t = _t.getFirstChild();
				{
				if (_t==null) _t=ASTNULL;
				switch ( _t.getType()) {
				case ID:
				{
					AST tmp18_AST = null;
					AST tmp18_AST_in = null;
					tmp18_AST = astFactory.create((AST)_t);
					tmp18_AST_in = (AST)_t;
					astFactory.addASTChild(currentAST, tmp18_AST);
					match(_t,ID);
					_t = _t.getNextSibling();
					{
					if (_t==null) _t=ASTNULL;
					switch ( _t.getType()) {
					case LCUR:
					{
						stmt_list(_t);
						_t = _retTree;
						astFactory.addASTChild(currentAST, returnAST);
						break;
					}
					case 3:
					{
						break;
					}
					default:
					{
						throw new NoViableAltException(_t);
					}
					}
					}
					break;
				}
				case LCUR:
				{
					stmt_list(_t);
					_t = _retTree;
					astFactory.addASTChild(currentAST, returnAST);
					break;
				}
				default:
				{
					throw new NoViableAltException(_t);
				}
				}
				}
				currentAST = __currentAST29;
				_t = __t29;
				_t = _t.getNextSibling();
				subgraph_AST = (AST)currentAST.root;
				break;
			}
			case LCUR:
			{
				stmt_list(_t);
				_t = _retTree;
				astFactory.addASTChild(currentAST, returnAST);
				subgraph_AST = (AST)currentAST.root;
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		returnAST = subgraph_AST;
		_retTree = _t;
	}
	
	public final void node_id(AST _t) throws RecognitionException {
		
		AST node_id_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST node_id_AST = null;
		
		try {      // for error handling
			{
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case ID:
			{
				AST tmp19_AST = null;
				AST tmp19_AST_in = null;
				tmp19_AST = astFactory.create((AST)_t);
				tmp19_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp19_AST);
				match(_t,ID);
				_t = _t.getNextSibling();
				break;
			}
			case COLON:
			{
				AST __t23 = _t;
				AST tmp20_AST = null;
				AST tmp20_AST_in = null;
				tmp20_AST = astFactory.create((AST)_t);
				tmp20_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp20_AST);
				ASTPair __currentAST23 = currentAST.copy();
				currentAST.root = currentAST.child;
				currentAST.child = null;
				match(_t,COLON);
				_t = _t.getFirstChild();
				AST tmp21_AST = null;
				AST tmp21_AST_in = null;
				tmp21_AST = astFactory.create((AST)_t);
				tmp21_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp21_AST);
				match(_t,ID);
				_t = _t.getNextSibling();
				{
				if (_t==null) _t=ASTNULL;
				switch ( _t.getType()) {
				case ID:
				{
					AST tmp22_AST = null;
					AST tmp22_AST_in = null;
					tmp22_AST = astFactory.create((AST)_t);
					tmp22_AST_in = (AST)_t;
					astFactory.addASTChild(currentAST, tmp22_AST);
					match(_t,ID);
					_t = _t.getNextSibling();
					break;
				}
				case 3:
				case COLON:
				{
					break;
				}
				default:
				{
					throw new NoViableAltException(_t);
				}
				}
				}
				{
				if (_t==null) _t=ASTNULL;
				switch ( _t.getType()) {
				case COLON:
				{
					compass(_t);
					_t = _retTree;
					astFactory.addASTChild(currentAST, returnAST);
					break;
				}
				case 3:
				{
					break;
				}
				default:
				{
					throw new NoViableAltException(_t);
				}
				}
				}
				currentAST = __currentAST23;
				_t = __t23;
				_t = _t.getNextSibling();
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
			}
			node_id_AST = (AST)currentAST.root;
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		returnAST = node_id_AST;
		_retTree = _t;
	}
	
	public final  boolean  a_list_node(AST _t) throws RecognitionException {
		 boolean record ;
		
		AST a_list_node_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST a_list_node_AST = null;
		AST s = null;
		AST s_AST = null;
		AST r = null;
		AST r_AST = null;
		record=false;
		
		try {      // for error handling
			{
			_loop64:
			do {
				if (_t==null) _t=ASTNULL;
				switch ( _t.getType()) {
				case EQUAL:
				{
					AST __t62 = _t;
					AST tmp23_AST = null;
					AST tmp23_AST_in = null;
					tmp23_AST = astFactory.create((AST)_t);
					tmp23_AST_in = (AST)_t;
					astFactory.addASTChild(currentAST, tmp23_AST);
					ASTPair __currentAST62 = currentAST.copy();
					currentAST.root = currentAST.child;
					currentAST.child = null;
					match(_t,EQUAL);
					_t = _t.getFirstChild();
					s = (AST)_t;
					AST s_AST_in = null;
					s_AST = astFactory.create(s);
					astFactory.addASTChild(currentAST, s_AST);
					match(_t,ID);
					_t = _t.getNextSibling();
					r = (AST)_t;
					AST r_AST_in = null;
					r_AST = astFactory.create(r);
					astFactory.addASTChild(currentAST, r_AST);
					match(_t,ID);
					_t = _t.getNextSibling();
					currentAST = __currentAST62;
					_t = __t62;
					_t = _t.getNextSibling();
					record |= (s.getText().equalsIgnoreCase("shape")
							&& (cleanAttribute(r.getText()).endsWith("record")));
					break;
				}
				case ID:
				{
					AST tmp24_AST = null;
					AST tmp24_AST_in = null;
					tmp24_AST = astFactory.create((AST)_t);
					tmp24_AST_in = (AST)_t;
					astFactory.addASTChild(currentAST, tmp24_AST);
					match(_t,ID);
					_t = _t.getNextSibling();
					break;
				}
				case LABEL:
				{
					AST __t63 = _t;
					AST tmp25_AST = null;
					AST tmp25_AST_in = null;
					tmp25_AST = astFactory.create((AST)_t);
					tmp25_AST_in = (AST)_t;
					astFactory.addASTChild(currentAST, tmp25_AST);
					ASTPair __currentAST63 = currentAST.copy();
					currentAST.root = currentAST.child;
					currentAST.child = null;
					match(_t,LABEL);
					_t = _t.getFirstChild();
					AST tmp26_AST = null;
					AST tmp26_AST_in = null;
					tmp26_AST = astFactory.create((AST)_t);
					tmp26_AST_in = (AST)_t;
					astFactory.addASTChild(currentAST, tmp26_AST);
					match(_t,ID);
					_t = _t.getNextSibling();
					currentAST = __currentAST63;
					_t = __t63;
					_t = _t.getNextSibling();
					break;
				}
				default:
				{
					break _loop64;
				}
				}
			} while (true);
			}
			a_list_node_AST = (AST)currentAST.root;
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		returnAST = a_list_node_AST;
		_retTree = _t;
		return record ;
	}
	
	public final void attr_list_edge(AST _t) throws RecognitionException {
		
		AST attr_list_edge_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST attr_list_edge_AST = null;
		
		try {      // for error handling
			AST __t37 = _t;
			AST tmp27_AST = null;
			AST tmp27_AST_in = null;
			tmp27_AST = astFactory.create((AST)_t);
			tmp27_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp27_AST);
			ASTPair __currentAST37 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,LBR);
			_t = _t.getFirstChild();
			{
			_loop39:
			do {
				if (_t==null) _t=ASTNULL;
				if ((_t.getType()==LABEL||_t.getType()==ID||_t.getType()==EQUAL)) {
					a_list_edge(_t);
					_t = _retTree;
					astFactory.addASTChild(currentAST, returnAST);
				}
				else {
					break _loop39;
				}
				
			} while (true);
			}
			currentAST = __currentAST37;
			_t = __t37;
			_t = _t.getNextSibling();
			attr_list_edge_AST = (AST)currentAST.root;
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		returnAST = attr_list_edge_AST;
		_retTree = _t;
	}
	
	public final void compass(AST _t) throws RecognitionException {
		
		AST compass_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST compass_AST = null;
		
		try {      // for error handling
			AST __t27 = _t;
			AST tmp28_AST = null;
			AST tmp28_AST_in = null;
			tmp28_AST = astFactory.create((AST)_t);
			tmp28_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp28_AST);
			ASTPair __currentAST27 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,COLON);
			_t = _t.getFirstChild();
			AST tmp29_AST = null;
			AST tmp29_AST_in = null;
			tmp29_AST = astFactory.create((AST)_t);
			tmp29_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp29_AST);
			match(_t,ID);
			_t = _t.getNextSibling();
			currentAST = __currentAST27;
			_t = __t27;
			_t = _t.getNextSibling();
			compass_AST = (AST)currentAST.root;
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		returnAST = compass_AST;
		_retTree = _t;
	}
	
	public final void attr_list_graph(AST _t) throws RecognitionException {
		
		AST attr_list_graph_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST attr_list_graph_AST = null;
		
		try {      // for error handling
			AST __t49 = _t;
			AST tmp30_AST = null;
			AST tmp30_AST_in = null;
			tmp30_AST = astFactory.create((AST)_t);
			tmp30_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp30_AST);
			ASTPair __currentAST49 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,LBR);
			_t = _t.getFirstChild();
			{
			_loop51:
			do {
				if (_t==null) _t=ASTNULL;
				if ((_t.getType()==LABEL||_t.getType()==ID||_t.getType()==EQUAL)) {
					a_list_graph(_t);
					_t = _retTree;
					astFactory.addASTChild(currentAST, returnAST);
				}
				else {
					break _loop51;
				}
				
			} while (true);
			}
			currentAST = __currentAST49;
			_t = __t49;
			_t = _t.getNextSibling();
			attr_list_graph_AST = (AST)currentAST.root;
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		returnAST = attr_list_graph_AST;
		_retTree = _t;
	}
	
	public final void attr_list_generic_node(AST _t) throws RecognitionException {
		
		AST attr_list_generic_node_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST attr_list_generic_node_AST = null;
		
		try {      // for error handling
			AST __t41 = _t;
			AST tmp31_AST = null;
			AST tmp31_AST_in = null;
			tmp31_AST = astFactory.create((AST)_t);
			tmp31_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp31_AST);
			ASTPair __currentAST41 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,LBR);
			_t = _t.getFirstChild();
			{
			_loop43:
			do {
				if (_t==null) _t=ASTNULL;
				if ((_t.getType()==LABEL||_t.getType()==ID||_t.getType()==EQUAL)) {
					a_list_generic_node(_t);
					_t = _retTree;
					astFactory.addASTChild(currentAST, returnAST);
				}
				else {
					break _loop43;
				}
				
			} while (true);
			}
			currentAST = __currentAST41;
			_t = __t41;
			_t = _t.getNextSibling();
			attr_list_generic_node_AST = (AST)currentAST.root;
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		returnAST = attr_list_generic_node_AST;
		_retTree = _t;
	}
	
	public final void attr_list_generic_edge(AST _t) throws RecognitionException {
		
		AST attr_list_generic_edge_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST attr_list_generic_edge_AST = null;
		
		try {      // for error handling
			AST __t45 = _t;
			AST tmp32_AST = null;
			AST tmp32_AST_in = null;
			tmp32_AST = astFactory.create((AST)_t);
			tmp32_AST_in = (AST)_t;
			astFactory.addASTChild(currentAST, tmp32_AST);
			ASTPair __currentAST45 = currentAST.copy();
			currentAST.root = currentAST.child;
			currentAST.child = null;
			match(_t,LBR);
			_t = _t.getFirstChild();
			{
			_loop47:
			do {
				if (_t==null) _t=ASTNULL;
				if ((_t.getType()==LABEL||_t.getType()==ID||_t.getType()==EQUAL)) {
					a_list_generic_edge(_t);
					_t = _retTree;
					astFactory.addASTChild(currentAST, returnAST);
				}
				else {
					break _loop47;
				}
				
			} while (true);
			}
			currentAST = __currentAST45;
			_t = __t45;
			_t = _t.getNextSibling();
			attr_list_generic_edge_AST = (AST)currentAST.root;
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		returnAST = attr_list_generic_edge_AST;
		_retTree = _t;
	}
	
	public final void a_list_edge(AST _t) throws RecognitionException {
		
		AST a_list_edge_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST a_list_edge_AST = null;
		
		try {      // for error handling
			{
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case EQUAL:
			{
				AST __t54 = _t;
				AST tmp33_AST = null;
				AST tmp33_AST_in = null;
				tmp33_AST = astFactory.create((AST)_t);
				tmp33_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp33_AST);
				ASTPair __currentAST54 = currentAST.copy();
				currentAST.root = currentAST.child;
				currentAST.child = null;
				match(_t,EQUAL);
				_t = _t.getFirstChild();
				AST tmp34_AST = null;
				AST tmp34_AST_in = null;
				tmp34_AST = astFactory.create((AST)_t);
				tmp34_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp34_AST);
				match(_t,ID);
				_t = _t.getNextSibling();
				AST tmp35_AST = null;
				AST tmp35_AST_in = null;
				tmp35_AST = astFactory.create((AST)_t);
				tmp35_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp35_AST);
				match(_t,ID);
				_t = _t.getNextSibling();
				currentAST = __currentAST54;
				_t = __t54;
				_t = _t.getNextSibling();
				break;
			}
			case ID:
			{
				AST tmp36_AST = null;
				AST tmp36_AST_in = null;
				tmp36_AST = astFactory.create((AST)_t);
				tmp36_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp36_AST);
				match(_t,ID);
				_t = _t.getNextSibling();
				break;
			}
			case LABEL:
			{
				AST __t55 = _t;
				AST tmp37_AST = null;
				AST tmp37_AST_in = null;
				tmp37_AST = astFactory.create((AST)_t);
				tmp37_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp37_AST);
				ASTPair __currentAST55 = currentAST.copy();
				currentAST.root = currentAST.child;
				currentAST.child = null;
				match(_t,LABEL);
				_t = _t.getFirstChild();
				AST tmp38_AST = null;
				AST tmp38_AST_in = null;
				tmp38_AST = astFactory.create((AST)_t);
				tmp38_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp38_AST);
				match(_t,ID);
				_t = _t.getNextSibling();
				currentAST = __currentAST55;
				_t = __t55;
				_t = _t.getNextSibling();
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
			}
			a_list_edge_AST = (AST)currentAST.root;
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		returnAST = a_list_edge_AST;
		_retTree = _t;
	}
	
	public final void a_list_generic_node(AST _t) throws RecognitionException {
		
		AST a_list_generic_node_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST a_list_generic_node_AST = null;
		
		try {      // for error handling
			{
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case EQUAL:
			{
				AST __t67 = _t;
				AST tmp39_AST = null;
				AST tmp39_AST_in = null;
				tmp39_AST = astFactory.create((AST)_t);
				tmp39_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp39_AST);
				ASTPair __currentAST67 = currentAST.copy();
				currentAST.root = currentAST.child;
				currentAST.child = null;
				match(_t,EQUAL);
				_t = _t.getFirstChild();
				AST tmp40_AST = null;
				AST tmp40_AST_in = null;
				tmp40_AST = astFactory.create((AST)_t);
				tmp40_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp40_AST);
				match(_t,ID);
				_t = _t.getNextSibling();
				AST tmp41_AST = null;
				AST tmp41_AST_in = null;
				tmp41_AST = astFactory.create((AST)_t);
				tmp41_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp41_AST);
				match(_t,ID);
				_t = _t.getNextSibling();
				currentAST = __currentAST67;
				_t = __t67;
				_t = _t.getNextSibling();
				break;
			}
			case ID:
			{
				AST tmp42_AST = null;
				AST tmp42_AST_in = null;
				tmp42_AST = astFactory.create((AST)_t);
				tmp42_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp42_AST);
				match(_t,ID);
				_t = _t.getNextSibling();
				break;
			}
			case LABEL:
			{
				AST __t68 = _t;
				AST tmp43_AST = null;
				AST tmp43_AST_in = null;
				tmp43_AST = astFactory.create((AST)_t);
				tmp43_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp43_AST);
				ASTPair __currentAST68 = currentAST.copy();
				currentAST.root = currentAST.child;
				currentAST.child = null;
				match(_t,LABEL);
				_t = _t.getFirstChild();
				AST tmp44_AST = null;
				AST tmp44_AST_in = null;
				tmp44_AST = astFactory.create((AST)_t);
				tmp44_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp44_AST);
				match(_t,ID);
				_t = _t.getNextSibling();
				currentAST = __currentAST68;
				_t = __t68;
				_t = _t.getNextSibling();
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
			}
			a_list_generic_node_AST = (AST)currentAST.root;
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		returnAST = a_list_generic_node_AST;
		_retTree = _t;
	}
	
	public final void a_list_generic_edge(AST _t) throws RecognitionException {
		
		AST a_list_generic_edge_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST a_list_generic_edge_AST = null;
		
		try {      // for error handling
			{
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case EQUAL:
			{
				AST __t71 = _t;
				AST tmp45_AST = null;
				AST tmp45_AST_in = null;
				tmp45_AST = astFactory.create((AST)_t);
				tmp45_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp45_AST);
				ASTPair __currentAST71 = currentAST.copy();
				currentAST.root = currentAST.child;
				currentAST.child = null;
				match(_t,EQUAL);
				_t = _t.getFirstChild();
				AST tmp46_AST = null;
				AST tmp46_AST_in = null;
				tmp46_AST = astFactory.create((AST)_t);
				tmp46_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp46_AST);
				match(_t,ID);
				_t = _t.getNextSibling();
				AST tmp47_AST = null;
				AST tmp47_AST_in = null;
				tmp47_AST = astFactory.create((AST)_t);
				tmp47_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp47_AST);
				match(_t,ID);
				_t = _t.getNextSibling();
				currentAST = __currentAST71;
				_t = __t71;
				_t = _t.getNextSibling();
				break;
			}
			case ID:
			{
				AST tmp48_AST = null;
				AST tmp48_AST_in = null;
				tmp48_AST = astFactory.create((AST)_t);
				tmp48_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp48_AST);
				match(_t,ID);
				_t = _t.getNextSibling();
				break;
			}
			case LABEL:
			{
				AST __t72 = _t;
				AST tmp49_AST = null;
				AST tmp49_AST_in = null;
				tmp49_AST = astFactory.create((AST)_t);
				tmp49_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp49_AST);
				ASTPair __currentAST72 = currentAST.copy();
				currentAST.root = currentAST.child;
				currentAST.child = null;
				match(_t,LABEL);
				_t = _t.getFirstChild();
				AST tmp50_AST = null;
				AST tmp50_AST_in = null;
				tmp50_AST = astFactory.create((AST)_t);
				tmp50_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp50_AST);
				match(_t,ID);
				_t = _t.getNextSibling();
				currentAST = __currentAST72;
				_t = __t72;
				_t = _t.getNextSibling();
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
			}
			a_list_generic_edge_AST = (AST)currentAST.root;
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		returnAST = a_list_generic_edge_AST;
		_retTree = _t;
	}
	
	public final void a_list_graph(AST _t) throws RecognitionException {
		
		AST a_list_graph_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		returnAST = null;
		ASTPair currentAST = new ASTPair();
		AST a_list_graph_AST = null;
		
		try {      // for error handling
			{
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case EQUAL:
			{
				AST __t58 = _t;
				AST tmp51_AST = null;
				AST tmp51_AST_in = null;
				tmp51_AST = astFactory.create((AST)_t);
				tmp51_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp51_AST);
				ASTPair __currentAST58 = currentAST.copy();
				currentAST.root = currentAST.child;
				currentAST.child = null;
				match(_t,EQUAL);
				_t = _t.getFirstChild();
				AST tmp52_AST = null;
				AST tmp52_AST_in = null;
				tmp52_AST = astFactory.create((AST)_t);
				tmp52_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp52_AST);
				match(_t,ID);
				_t = _t.getNextSibling();
				AST tmp53_AST = null;
				AST tmp53_AST_in = null;
				tmp53_AST = astFactory.create((AST)_t);
				tmp53_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp53_AST);
				match(_t,ID);
				_t = _t.getNextSibling();
				currentAST = __currentAST58;
				_t = __t58;
				_t = _t.getNextSibling();
				break;
			}
			case ID:
			{
				AST tmp54_AST = null;
				AST tmp54_AST_in = null;
				tmp54_AST = astFactory.create((AST)_t);
				tmp54_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp54_AST);
				match(_t,ID);
				_t = _t.getNextSibling();
				break;
			}
			case LABEL:
			{
				AST __t59 = _t;
				AST tmp55_AST = null;
				AST tmp55_AST_in = null;
				tmp55_AST = astFactory.create((AST)_t);
				tmp55_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp55_AST);
				ASTPair __currentAST59 = currentAST.copy();
				currentAST.root = currentAST.child;
				currentAST.child = null;
				match(_t,LABEL);
				_t = _t.getFirstChild();
				AST tmp56_AST = null;
				AST tmp56_AST_in = null;
				tmp56_AST = astFactory.create((AST)_t);
				tmp56_AST_in = (AST)_t;
				astFactory.addASTChild(currentAST, tmp56_AST);
				match(_t,ID);
				_t = _t.getNextSibling();
				currentAST = __currentAST59;
				_t = __t59;
				_t = _t.getNextSibling();
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
			}
			a_list_graph_AST = (AST)currentAST.root;
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		returnAST = a_list_graph_AST;
		_retTree = _t;
	}
	
	
	public static final String[] _tokenNames = {
		"<0>",
		"EOF",
		"<2>",
		"NULL_TREE_LOOKAHEAD",
		"\"graph\"",
		"\"digraph\"",
		"\"subgraph\"",
		"\"node\"",
		"\"edge\"",
		"\"strict\"",
		"\"label\"",
		"an identifier",
		"LCUR",
		"SEMI",
		"RCUR",
		"EQUAL",
		"HTML",
		"LBR",
		"RBR",
		"COMMA",
		"D_EDGE_OP",
		"ND_EDGE_OP",
		"COLON",
		"WS",
		"CMT",
		"CPP_COMMENT",
		"ESC",
		"LT",
		"GT"
	};
	
	private static final long[] mk_tokenSet_0() {
		long[] data = { 7511504L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_0 = new BitSet(mk_tokenSet_0());
	}
	
